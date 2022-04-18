#include "./src/Shader.h"
#include "./src/VAOManager.h"
#include "./src/util.h"
#include <stb/stb_image.h>
#include <cmath>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//int main() {
//    int width, height, nrChannels;
//    unsigned char *data = stbi_load(R"(D:\Projects\C++\learn_opengl\resources\hutao.jpeg)", &width, &height, &nrChannels, 0);
//    std::cout << width << ", " << height << ", " << nrChannels << std::endl;
//}

int main() {
    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
    };

    VAOManager vaoManager(vertices, sizeof(vertices), indices, sizeof(indices));
    Shader shader(R"(D:\Projects\C++\learn_opengl\resources\shader\hello.vert)", R"(D:\Projects\C++\learn_opengl\resources\shader\hello.frag)");

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
        glBindVertexArray(vaoManager.VAO);
        vaoManager.drawElements();
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

