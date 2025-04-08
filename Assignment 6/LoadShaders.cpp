#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

GLuint LoadShader(const char* path, GLenum shaderType) {
    if (path == nullptr || path[0] == '\0') {
        return 0; // Skip empty shaders
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader: " << path << std::endl;
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    const char* codeCStr = code.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &codeCStr, NULL);
    glCompileShader(shader);

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compile error (" << path << "):\n" << infoLog << std::endl;
    }

    return shader;
}

// Define the 5-argument version first
GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path,
                   const char* tessControl_file_path,
                   const char* tessEval_file_path,
                   const char* geometry_file_path) {
    GLuint vertexShader = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint fragmentShader = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);
    GLuint tessControlShader = LoadShader(tessControl_file_path, GL_TESS_CONTROL_SHADER);
    GLuint tessEvalShader = LoadShader(tessEval_file_path, GL_TESS_EVALUATION_SHADER);
    GLuint geometryShader = LoadShader(geometry_file_path, GL_GEOMETRY_SHADER);

    GLuint program = glCreateProgram();
    if (vertexShader) glAttachShader(program, vertexShader);
    if (fragmentShader) glAttachShader(program, fragmentShader);
    if (tessControlShader) glAttachShader(program, tessControlShader);
    if (tessEvalShader) glAttachShader(program, tessEvalShader);
    if (geometryShader) glAttachShader(program, geometryShader);
    
    glLinkProgram(program);

    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader program link error:\n" << infoLog << std::endl;
    }

    // Clean up
    if (vertexShader) glDeleteShader(vertexShader);
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (tessControlShader) glDeleteShader(tessControlShader);
    if (tessEvalShader) glDeleteShader(tessEvalShader);
    if (geometryShader) glDeleteShader(geometryShader);

    return program;
}

// Now the 2-arg version can call the 5-arg version
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    return LoadShaders(vertex_file_path, fragment_file_path, "", "", "");
}
