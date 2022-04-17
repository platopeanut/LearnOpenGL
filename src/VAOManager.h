//
// Created by 28571 on 2022/4/17.
//

#ifndef LEARN_OPENGL_VAOMANAGER_H
#define LEARN_OPENGL_VAOMANAGER_H

#include <glad/glad.h>

class VAOManager {
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    float* vertices;
    int size_of_vertex;
    unsigned int* indices;
    int size_of_index;
    int num_of_tri;
    VAOManager(float* vertices, int size_of_vertex, unsigned int* indices, int size_of_index)
            : vertices(vertices), indices(indices), size_of_vertex(size_of_vertex), size_of_index(size_of_index) {
        num_of_tri = size_of_index / sizeof(unsigned int) / 3;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size_of_vertex, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_index, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    ~VAOManager() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void drawElements() {
        glDrawElements(GL_TRIANGLES, num_of_tri * 3, GL_UNSIGNED_INT, 0);
    }
    void drawArrays() {
        glDrawArrays(GL_TRIANGLES, 0, num_of_tri);
    }
};

#endif //LEARN_OPENGL_VAOMANAGER_H
