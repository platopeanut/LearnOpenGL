#include "../src/Shader.h"
#include "../src/VAOManager.h"
#include "../src/util.h"
#include <gtest/gtest.h>
#include <stb/stb_image.h>
#include <cmath>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

TEST(texture, multi_texture){
    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
    };

//    auto config_texture = [](unsigned int& texture, const char * filename) {
//
//    };

//    config_texture(texture2, R"(D:\Projects\C++\learn_opengl\resources\texture\hutao.jpeg)");
//    config_texture(texture1, R"(D:\Projects\C++\learn_opengl\resources\texture\wanye.jpg)");

    unsigned int texture[2];
    const char * filename[2] = {
            R"(D:\Projects\C++\learn_opengl\resources\texture\hutao.jpeg)",
            R"(D:\Projects\C++\learn_opengl\resources\texture\wanye.jpg)"
    };
    for (int i = 0; i < 2; ++i) {
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        // 设置纹理环绕，过滤方式
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 加载，生成纹理
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char * data = stbi_load(filename[i], &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        std::cout << width << ", " << height << std::endl;
    }





    VAOManager vaoManager(vertices, sizeof(vertices), indices, sizeof(indices), [](){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    });
    Shader shader(R"(D:\Projects\C++\learn_opengl\resources\shader\hello.vert)",
                  R"(D:\Projects\C++\learn_opengl\resources\shader\hello.frag)");
    // 切记！！！设置uniform之前一定先use();
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
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
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
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
}


