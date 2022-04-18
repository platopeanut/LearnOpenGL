#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexSrc, const char* fragmentSrc, bool isFile = true);
    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat4(const std::string& name, float x, float y, float z, float w) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};


#endif //LEARN_OPENGL_SHADER_H
