#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

// Include GLEW, GLFW, and GLM.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Declaration for our BMP loader.
void loadAutoBMP(const char* imagePath,
                 unsigned char** data,
                 unsigned int* width,
                 unsigned int* height,
                 unsigned short* bpp,
                 unsigned int* format,
                 unsigned int* internalFormat);

//----------------------------------------------
// Structures for mesh data
//----------------------------------------------
struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;      // Default white if not provided.
    glm::vec2 texCoords;
};

struct TriData {
    unsigned int indices[3];
};

//----------------------------------------------
// Minimal ASCII PLY parser.
// Assumes each vertex has 8 properties: x, y, z, nx, ny, nz, u, v.
//----------------------------------------------
void readPLYFile(const std::string& fname, 
                 std::vector<VertexData>& vertices,
                 std::vector<TriData>& faces)
{
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Could not open PLY file: " << fname << std::endl;
        return;
    }
    
    std::string line;
    int vertexCount = 0, faceCount = 0;
    bool headerEnded = false;
    while (std::getline(file, line)) {
        if (line.substr(0, 14) == "element vertex") {
            std::istringstream iss(line);
            std::string dummy;
            iss >> dummy >> dummy >> vertexCount;
        } else if (line.substr(0, 12) == "element face") {
            std::istringstream iss(line);
            std::string dummy;
            iss >> dummy >> dummy >> faceCount;
        } else if (line == "end_header") {
            headerEnded = true;
            break;
        }
    }
    if (!headerEnded) {
        std::cerr << "PLY header did not end properly in " << fname << std::endl;
        return;
    }
    
    // Read vertices (8 floats per vertex).
    for (int i = 0; i < vertexCount; ++i) {
        if (!std::getline(file, line))
            break;
        std::istringstream iss(line);
        VertexData v;
        iss >> v.position.x >> v.position.y >> v.position.z;
        iss >> v.normal.x   >> v.normal.y   >> v.normal.z;
        iss >> v.texCoords.x >> v.texCoords.y;
        v.color = glm::vec3(1.0f);  // Default color: white.
        vertices.push_back(v);
    }
    
    // Read faces (each face should list 3 vertex indices).
    for (int i = 0; i < faceCount; ++i) {
        if (!std::getline(file, line))
            break;
        std::istringstream iss(line);
        int count;
        iss >> count;
        if (count != 3) {
            std::cerr << "Warning: Only triangular faces are supported in " << fname << std::endl;
            continue;
        }
        TriData tri;
        iss >> tri.indices[0] >> tri.indices[1] >> tri.indices[2];
        faces.push_back(tri);
    }
    file.close();
}

//----------------------------------------------
// Shader helper functions
//----------------------------------------------
GLuint compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
    }
    return shader;
}

GLuint createShaderProgram(const std::string& vSource, const std::string& fSource) {
    GLuint vShader = compileShader(GL_VERTEX_SHADER, vSource);
    GLuint fShader = compileShader(GL_FRAGMENT_SHADER, fSource);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vShader);
    glAttachShader(prog, fShader);
    glLinkProgram(prog);

    int success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(prog, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Error:\n" << infoLog << std::endl;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return prog;
}

//----------------------------------------------
// TexturedMesh class encapsulates a textured triangle mesh.
//----------------------------------------------
class TexturedMesh {
public:
    std::vector<VertexData> vertices;
    std::vector<TriData> faces;
    GLuint vao, vbo, ebo;
    GLuint textureID;
    GLuint shaderProgram;

    TexturedMesh(const std::string& plyPath, const std::string& bmpPath) {
        // Load mesh data from the PLY file.
        readPLYFile(plyPath, vertices, faces);
        std::cout << "Loaded " << vertices.size() << " vertices and " 
                  << faces.size() << " faces from " << plyPath << std::endl;

        // Load texture using our BMP loader.
        unsigned char* imageData = nullptr;
        unsigned int texW = 0, texH = 0;
        unsigned short bpp = 0;
        unsigned int fmt = 0, intFmt = 0;
        loadAutoBMP(bmpPath.c_str(), &imageData, &texW, &texH, &bpp, &fmt, &intFmt);
        if (!imageData) {
            std::cerr << "Failed to load texture: " << bmpPath << std::endl;
        }

        // Create texture object.
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, intFmt, texW, texH, 0, fmt, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        delete[] imageData;

        // Create VAO, VBO, and EBO.
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(TriData), faces.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers.
        // Position (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
        glEnableVertexAttribArray(0);
        // Normal (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
        glEnableVertexAttribArray(1);
        // Color (location = 2)
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
        glEnableVertexAttribArray(2);
        // Texture Coordinates (location = 3)
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texCoords));
        glEnableVertexAttribArray(3);
        glBindVertexArray(0);

        // Create shader program.
        // GLSL version 150 is used to be compatible with macOS OpenGL 3.2 Core Profile.
        std::string vertexShaderSource = R"(
            #version 150
            in vec3 aPos;
            in vec3 aNormal;
            in vec3 aColor;
            in vec2 aTexCoord;
            
            uniform mat4 MVP;
            
            out vec3 ourColor;
            out vec2 TexCoord;
            
            void main(){
                gl_Position = MVP * vec4(aPos, 1.0);
                ourColor = aColor;
                TexCoord = aTexCoord;
            }
        )";

        std::string fragmentShaderSource = R"(
            #version 150
            in vec3 ourColor;
            in vec2 TexCoord;
            out vec4 FragColor;
            
            uniform sampler2D texture1;
            
            void main(){
                vec4 texColor = texture(texture1, TexCoord);
                FragColor = texColor * vec4(ourColor, 1.0);
            }
        )";

        shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    void draw(const glm::mat4& mvp) {
        glUseProgram(shaderProgram);
        GLuint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

//----------------------------------------------
// Basic first-person camera variables and functions.
//----------------------------------------------
glm::vec3 cameraPos = glm::vec3(0.5f, 0.4f, 0.5f);
float cameraYaw     = 0.0f; // 0° means looking toward negative Z.
const float moveSpeed = 0.05f;
const float rotSpeed  = 3.0f; // degrees per frame

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        float yawRad = glm::radians(cameraYaw);
        glm::vec3 forward(sin(yawRad), 0.f, -cos(yawRad));
        cameraPos += moveSpeed * forward;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        float yawRad = glm::radians(cameraYaw);
        glm::vec3 backward(-sin(yawRad), 0.f, cos(yawRad));
        cameraPos += moveSpeed * backward;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cameraYaw += rotSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cameraYaw -= rotSpeed;
    }
}

//----------------------------------------------
// Main function
//----------------------------------------------
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW.\n";
        return -1;
    }
    // Request OpenGL 3.2 Core Profile (required on macOS)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Assignment 4: Textured Meshes", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW.\n";
        glfwTerminate();
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    int screenW, screenH;
    glfwGetFramebufferSize(window, &screenW, &screenH);
    glViewport(0, 0, screenW, screenH);
    
    float aspect = static_cast<float>(screenW) / screenH;
    glm::mat4 projection = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);
    
    // Create TexturedMesh objects.
    // (File names here include WindowBG.ply – note the capitalization must match your file names.)
    std::vector<TexturedMesh> meshes;
    meshes.push_back(TexturedMesh("LinksHouse/Walls.ply",    "LinksHouse/walls.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/WindowBG.ply", "LinksHouse/windowbg.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/Table.ply",    "LinksHouse/table.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/MetalObjects.ply", "LinksHouse/metalobjects.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/Patio.ply",    "LinksHouse/patio.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/DoorBG.ply",   "LinksHouse/doorbg.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/Curtains.ply", "LinksHouse/curtains.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/Bottles.ply",  "LinksHouse/bottles.bmp"));
    meshes.push_back(TexturedMesh("LinksHouse/WoodObjects.ply", "LinksHouse/woodobjects.bmp"));
    
    // Main render loop.
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float yawRad = glm::radians(cameraYaw);
        glm::vec3 camDir(sin(yawRad), 0.f, -cos(yawRad));
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + camDir, glm::vec3(0,1,0));
        glm::mat4 mvp  = projection * view;
        
        // Draw each mesh.
        for (auto& mesh : meshes) {
            mesh.draw(mvp);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
