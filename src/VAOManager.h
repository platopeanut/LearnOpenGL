//
// Created by 28571 on 2022/4/17.
//

#ifndef LEARN_OPENGL_VAOMANAGER_H
#define LEARN_OPENGL_VAOMANAGER_H

#include <glad/glad.h>

class VAOManager {
public:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    int num_of_tri;
    VAOManager(float* vertices, int size_of_vertex, unsigned int* indices, int size_of_index, void(*vertexAttribPointerCallback)()) {
        num_of_tri = size_of_index / (int) sizeof(unsigned int) / 3;
        // create
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // 绑定
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size_of_vertex, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_index, indices, GL_STATIC_DRAW);
        // 解析顶点属性内存布局
        vertexAttribPointerCallback();
        // 解除绑定
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    VAOManager(float* vertices, int size_of_vertex, void(*vertexAttribPointerCallback)()) {
        num_of_tri = (int) (size_of_vertex / (3 * sizeof(float)));
        // create
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        // 绑定
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size_of_vertex, vertices, GL_STATIC_DRAW);
        // 解析顶点属性内存布局
        vertexAttribPointerCallback();
        // 解除绑定
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    ~VAOManager() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void drawElements() const {
        glDrawElements(GL_TRIANGLES, num_of_tri * 3, GL_UNSIGNED_INT, nullptr);
    }
    void drawArrays() const {
        glDrawArrays(GL_TRIANGLES, 0, num_of_tri);
    }
};

#endif //LEARN_OPENGL_VAOMANAGER_H
