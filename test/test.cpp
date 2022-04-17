#include <gtest/gtest.h>
#include "../src/Shader.h"
#include "../src/VAOManager.h"
#include "../src/util.h"
#include <cmath>

void processInput(GLFWwindow *window);

TEST(hello, world) {
    GLFWwindow* window = createWindow(600, 400, "Learn OpenGL Test");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        // handle event
        processInput(window);
        // render
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // -----
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(0);
}

/**
 *  shader 数据传递
 *  1. out -> int
 *  2. cpu -> gpu (uniform)
 *  3. vertex attribute
 */

TEST(shader, uniform) {
    GLFWwindow* window = createWindow(600, 400, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices1[] = {
            -0.5f, 0.7f, 0.0f,
            0.0f, 0.0f, 0.0f,
            -0.3f, -0.4f, 0.0f,
            0.3f, -0.4f, 0.0f,
            0.5f, 0.7f, 0.0f,
            0.0f, 0.8f, 0.0f
    };
    float vertices2[] = {
            -0.5f, 0.3f, 0.0f,
            0.5f, 0.3f, 0.0f,
            -0.5f, -0.3f, 0.0f,
            0.5f, -0.3f, 0.0f,
    };
    unsigned int indices1[] = {
            0, 1, 2,
            1, 3, 4,
            5, 3, 2
    };
    unsigned int indices2[] = {
            0, 1, 2,
            1, 2, 3,
    };
    VAOManager vaoManager1(vertices1, sizeof(vertices1), indices1, sizeof(indices1));
    VAOManager vaoManager2(vertices2, sizeof(vertices2), indices2, sizeof(indices2));
    Shader shader(R"(D:\Projects\C++\learn_opengl\shader\hello.vert)", R"(D:\Projects\C++\learn_opengl\shader\hello.frag)");

//    图元装配设置
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);
        // render
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw
        shader.use();
        float redValue = (float) sin(glfwGetTime()*10.0f)/2.0f + 0.5f;
        shader.setFloat4("aColor", redValue, 0, 0, 1);
        glBindVertexArray(vaoManager2.VAO);
        vaoManager2.drawElements();
        glBindVertexArray(vaoManager1.VAO);
        vaoManager1.drawElements();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

