#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    // Compile shaders
    compileShader(vertex, vShaderCode, GL_VERTEX_SHADER);
    compileShader(fragment, fShaderCode, GL_FRAGMENT_SHADER);

    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    checkCompileErrors(this->Program, "PROGRAM");

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->Program);
}

void Shader::use() const {
    glUseProgram(Program);
}

std::string Shader::loadShaderSource(const char* shaderPath) {
    std::string code;
    std::ifstream shaderFile;

    // Ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open file
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // Read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // Close file handlers
        shaderFile.close();
        // Convert stream into string
        code = shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    return code;
}

void Shader::compileShader(GLuint& shaderID, const GLchar* shaderSource, GLenum shaderType) {
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    checkCompileErrors(shaderID, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

GLuint Shader::load(const char* vertexPath, const char* fragmentPath) {
    Shader shader(vertexPath, fragmentPath);
    return shader.Program;
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}