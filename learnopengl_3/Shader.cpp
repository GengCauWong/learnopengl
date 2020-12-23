//
// Created by timothy on 12/15/20.
//

#include "Shader.h"
#include <iostream>

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    GLint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexSource, NULL);
    glCompileShader(vShader);

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "Failed to create v shader" << std::endl;
        glGetProgramInfoLog(vShader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: VShader\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return;
    }


    GLint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragmentSource, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "Failed to create f shader" << std::endl;
        GLchar infoLog2[1024];
        glGetProgramInfoLog(fShader, 1024, NULL, infoLog2);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: FShader\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::cout << "Failed to link program" << std::endl;
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        return;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (GLint)value);
}
void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}