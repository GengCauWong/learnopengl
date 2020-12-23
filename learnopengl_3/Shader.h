//
// Created by timothy on 12/15/20.
//

#ifndef LEARNOPENGL_2_SHADER_H
#define LEARNOPENGL_2_SHADER_H

#include "glad/glad.h"
#include <string>

class Shader {
public:
    GLint shaderProgram;

    Shader(const char* vertexSource, const char* fragmentSource);
    void use();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
};


#endif //LEARNOPENGL_2_SHADER_H
