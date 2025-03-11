#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

// Add inline to prevent duplicate symbols
inline void checkLinkingErrors(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    static GLuint load(const char* vertexPath, const char* fragmentPath);
    void checkLinkingErrors(GLuint program);
    GLuint ID; // Shader program ID

    void use() { glUseProgram(ID); }

    // Implement getUniformLocation method
    GLint getUniformLocation(const std::string& name) {
        return glGetUniformLocation(ID, name.c_str());
    }

private:
    GLuint Program;
    static std::string loadShaderSource(const char* filePath);
    static void compileShader(GLuint& shaderID, const GLchar* source, GLenum type);
    static void checkCompileErrors(GLuint shader, std::string type);
};

#endif // SHADER_H
