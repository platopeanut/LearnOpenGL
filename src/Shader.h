//
// Created by 28571 on 2022/4/16.
//

#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat4(const std::string& name, float x, float y, float z, float w) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //LEARN_OPENGL_SHADER_H
