#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h> // Include GLEW to manage OpenGL extensions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Headers/stb_image.h"
#include "Headers/TexturedMesh.h"
GLFWwindow* window;
using namespace glm;
GLuint VAO, VBO, shaderProgram, texture;  // Define them globally

/**
 * Given a file path imagepath, read the data in that bitmapped image
 * and return the raw bytes of color in the data pointer.
 * The width and height of the image are returned in the weight and height pointers,
 * respectively.
 *
 * usage:
 *
 * unsigned char* imageData;
 * unsigned int width, height;
 * loadARGB_BMP("mytexture.bmp", &imageData, &width, &height);
 *
 * Modified from https://github.com/opengl-tutorials/ogl.
 */
void loadARGB_BMP(const char* imagepath, unsigned char** data, unsigned int* width, unsigned int* height) {

    printf("Reading image %s\n", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    // Actual RGBA data

    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file){
        printf("%s could not be opened. Are you in the right directory?\n", imagepath);
        getchar();
        return;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, problem
    if ( fread(header, 1, 54, file)!=54 ){
        printf("Not a correct BMP file1\n");
        fclose(file);
        return;
    }

    // Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    *width      = *(int*)&(header[0x12]);
    *height     = *(int*)&(header[0x16]);
    // A BMP files always begins with "BM"
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file2\n");
        fclose(file);
        return;
    }
    // Make sure this is a 32bpp file
    if ( *(int*)&(header[0x1E])!=3  ) {
        printf("Not a correct BMP file3\n");
        fclose(file);
        return;
    }
    // fprintf(stderr, "header[0x1c]: %d\n", *(int*)&(header[0x1c]));
    // if ( *(int*)&(header[0x1C])!=32 ) {
    //     printf("Not a correct BMP file4\n");
    //     fclose(file);
    //     return;
    // }

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=(*width)* (*height)*4; // 4 : one byte for each Red, Green, Blue, Alpha component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    *data = new unsigned char [imageSize];

    if (dataPos != 54) {
        fread(header, 1, dataPos - 54, file);
    }

    // Read the actual data from the file into the buffer
    fread(*data,1,imageSize,file);

    // Everything is in memory now, the file can be closed.
    fclose (file);
}

GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint setupShaders() {
    // Vertex and Fragment shader sources
    const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout(location = 0) in vec3 vertexPosition_modelspace;
        layout(location = 1) in vec2 vertexUV;
        out vec2 UV;
        uniform mat4 MVP;
        void main(){
            gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
            UV = vertexUV;
        }
    )glsl";

    const char* fragmentShaderSource = R"glsl(
        #version 330 core
        in vec2 UV;
        out vec3 color;
        uniform sampler2D myTextureSampler;
        void main(){
            color = texture(myTextureSampler, UV).rgb;
        }
    )glsl";

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    checkLinkingErrors(program);

    glDeleteShader(vertexShader);  // Cleanup after linking
    glDeleteShader(fragmentShader);  // Cleanup after linking

    return program;  // Return the program ID
}

void checkShaderCompilation(GLuint shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void cleanup(std::vector<TexturedMesh>& meshes) {
    for (auto& mesh : meshes) {
        mesh.cleanup(); // Calls the cleanup function inside TexturedMesh class
    }
    meshes.clear();

    // OpenGL Cleanup
    extern GLuint VAO;
    extern GLuint VBO;
    extern GLuint shaderProgram;
    extern GLuint texture;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);

    glfwTerminate(); // Clean up GLFW resources
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Initialize OpenGL context and window using GLFW
    int windowWidth = 800; // UPDATE LATER
    int windowHeight = 600; // UPDATE LATER

    // Setup camera and projection matrix
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, windowWidth, windowHeight);

    // Build and compile our shader program
    GLuint shaderProgram = setupShaders(); // See function setupShaders() for implementation details
    glUseProgram(shaderProgram);

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    glBindVertexArray(0);

    // Set up depth testing
    glEnable(GL_DEPTH_TEST);

    GLuint textureID = glGetUniformLocation(shaderProgram, "myTextureSampler");
    glActiveTexture(GL_TEXTURE0);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);    
    glUniform1i(textureID, 0);  // Texture unit 0 is for base images.

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);  // numVertices needs to be set to the correct number of vertices
    glBindVertexArray(0);

    // Initialize camera and projection data
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    glm::mat4 MVP = projection * view * model;

    // Assuming you have calculated your MVP matrix
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // Create TexturedMesh instances
    std::vector<TexturedMesh> meshes;
    meshes.emplace_back("LinksHouse/Bottles.ply", "LinksHouse/Bottles.bmp");
    meshes.emplace_back("LinksHouse/Curtains.ply", "LinksHouse/Curtains.bmp");
    meshes.emplace_back("LinksHouse/DoorBG.ply", "LinksHouse/DoorBG.bmp");
    meshes.emplace_back("LinksHouse/Floor.ply", "LinksHouse/Floor.bmp");
    meshes.emplace_back("LinksHouse/MetalObjects.ply", "LinksHouse/MetalObjects.bmp");
    meshes.emplace_back("LinksHouse/Patio.ply", "LinksHouse/Patio.bmp");
    meshes.emplace_back("LinksHouse/Table.ply", "LinksHouse/Table.bmp");
    meshes.emplace_back("LinksHouse/Walls.ply", "LinksHouse/Walls.bmp");
    meshes.emplace_back("LinksHouse/WindowBG.ply", "LinksHouse/WindowBG.bmp");
    meshes.emplace_back("LinksHouse/WoodObjects.ply", "LinksHouse/WoodObjects.bmp");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glBindVertexArray(0); // no need to unbind it every time 

        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW, clearing any resources allocated by GLFW.
    cleanup(meshes); // Clean up all resources
    glfwTerminate();
    return 0;
}
