#define GLM_ENABLE_EXPERIMENTAL

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

// Include GLEW (must be before gl.h and glfw3.h)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  // for transformations
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

// Vertex positions for a triangle
GLfloat g_vert_buffer[] = {
    0.0f,  0.8f, 0.0f,
    0.8f, -0.5f, 0.0f,
   -0.8f, -0.5f, 0.0f,
};

// UV coordinates for each vertex
GLfloat g_uv_buffer[] = {
    0.5f, 0.5f,
    0.20f, 0.20f,
    0.8f, 0.20f,
};

// Indices for drawing the triangle
GLuint indexArray[] = {
    0, 1, 2
};

unsigned char TEXTURE_SIZE = 32;

void createTextureImage(GLfloat** texPixels, float R, float G, float B) {
    int textureSize = TEXTURE_SIZE;
    *texPixels = (GLfloat*) malloc(3 * sizeof(GLfloat) * textureSize * textureSize);
    float sigma2 = textureSize * 0.5f;
    for (int i = 0; i < textureSize; ++i) {
        float i1 = i - textureSize / 2.0f;
        for (int j = 0; j < textureSize; ++j) {
            float j1 = j - textureSize / 2.0f;
            int baseIdx = i * (textureSize * 3) + j * 3;
            float exponent = -((i1 * i1) / (2 * sigma2) + (j1 * j1) / (2 * sigma2));
            (*texPixels)[baseIdx + 0] = pow(R * exp(exponent), 2.2f);
            (*texPixels)[baseIdx + 1] = pow(G * exp(exponent), 2.2f);
            (*texPixels)[baseIdx + 2] = pow(B * exp(exponent), 2.2f);
        }
    }
}

int main( int argc, char* argv[] ) {

    // Initialize GLFW
    if (!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    // Create a windowed mode window and its OpenGL context.
    float screenW = 1400;
    float screenH = 900;
    window = glfwCreateWindow(screenW, screenH, "An Example", NULL, NULL);
    if(window == NULL){
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Create shader objects
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Vertex Shader (GLSL version 120)
    std::string VertexShaderCode = "\
#version 120\n\
\n\
// Vertex attributes\n\
attribute vec3 vertexPosition_modelspace;\n\
attribute vec2 vertexUV;\n\
\n\
// Varying to pass UV to fragment shader\n\
varying vec2 UV;\n\
\n\
void main(){\n\
    gl_Position = vec4(vertexPosition_modelspace, 1.0);\n\
    UV = vertexUV;\n\
}\n";

    // Fragment Shader (GLSL version 120)
    std::string FragmentShaderCode = "\
#version 120\n\
\n\
// Varying coming from vertex shader\n\
varying vec2 UV;\n\
\n\
// Uniforms\n\
uniform sampler2D tex1;\n\
uniform sampler2D tex2;\n\
uniform float blend1;\n\
uniform float blend2;\n\
\n\
void main(){\n\
    vec4 color1 = texture2D(tex1, UV);\n\
    vec4 color2 = texture2D(tex2, UV);\n\
    gl_FragColor = blend1 * color1 + blend2 * color2;\n\
}\n";

    // Compile the Vertex Shader
    const char* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile the Fragment Shader
    const char* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the shader program
    GLuint ProgramID = glCreateProgram();
    // Bind attributes manually before linking (for GLSL 120, "attribute" semantics apply)
    glBindAttribLocation(ProgramID, 0, "vertexPosition_modelspace");
    glBindAttribLocation(ProgramID, 1, "vertexUV");

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    // Get uniform locations
    GLuint tex1ID = glGetUniformLocation(ProgramID, "tex1");
    GLuint tex2ID = glGetUniformLocation(ProgramID, "tex2");
    float blend1Val = 0.5f;
    float blend2Val = 0.5f;
    GLuint blend1ID = glGetUniformLocation(ProgramID, "blend1");
    GLuint blend2ID = glGetUniformLocation(ProgramID, "blend2");

    // Generate textures
    GLuint textureID[2];
    glGenTextures(2, textureID);

    // Texture 1: green texture
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_RGB, GL_FLOAT, 0);
    GLfloat* texPixels = NULL;
    createTextureImage(&texPixels, 0.0f, 1.0f, 0.0f);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TEXTURE_SIZE, TEXTURE_SIZE, GL_RGB, GL_FLOAT, texPixels);
    free(texPixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Texture 2: blue texture
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_RGB, GL_FLOAT, 0);
    texPixels = NULL;
    createTextureImage(&texPixels, 0.0f, 0.0f, 1.0f);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, TEXTURE_SIZE, TEXTURE_SIZE, GL_RGB, GL_FLOAT, texPixels);
    free(texPixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set up input mode for escape key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set clear color (indigo background)
    glClearColor(0.2f, 0.2f, 0.3f, 0.0f);

    // Main loop
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program and set uniforms
        glUseProgram(ProgramID);
        glUniform1f(blend1ID, blend1Val);
        glUniform1f(blend2ID, blend2Val);
        glUniform1i(tex1ID, 0);
        glUniform1i(tex2ID, 1);

        // Activate textures and bind
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID[1]);

        // Enable vertex attribute arrays
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,            // attribute index 0
            3,            // 3 components per vertex (x,y,z)
            GL_FLOAT,
            GL_FALSE,
            0,
            g_vert_buffer
        );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,            // attribute index 1
            2,            // 2 components per vertex (u,v)
            GL_FLOAT,
            GL_FALSE,
            0,
            g_uv_buffer
        );

        // Draw the triangle using indices
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indexArray);

        // Unbind textures
        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);

    glfwTerminate();
    return 0;
}