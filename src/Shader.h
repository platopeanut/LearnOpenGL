#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    void setFloatV4(const std::string& name, float x, float y, float z, float w) const;
    void setFloatM4(const std::string& name, glm::mat4 transform) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};


#endif //LEARN_OPENGL_SHADER_H
