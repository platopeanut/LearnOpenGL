#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./src/Shader.h"
#include "./src/VAOManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* createWindow(int width, int height, const char* title) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    return window;
}
int main() {
    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL Main");
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
        glBindVertexArray(vaoManager2.VAO);
        vaoManager2.drawElements();
        shader.use();
        glBindVertexArray(vaoManager1.VAO);
        vaoManager1.drawElements();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}