#include <gtest/gtest.h>
#include "../src/Shader.h"
#include "../src/VAOManager.h"
#include "../src/util.h"
#include <cmath>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

TEST(shader, two_object) {
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
    VAOManager vaoManager1(vertices1, sizeof(vertices1), indices1, sizeof(indices1), [](){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
    });
    VAOManager vaoManager2(vertices2, sizeof(vertices2), indices2, sizeof(indices2), [](){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
    });
    const char* vertexShaderCode = "#version 330 core\n"
                                   "layout(location = 0) in vec3 aPos;\n"
                                   "void main() {\n"
                                   "gl_Position = vec4(aPos, 1.0);\n"
                                   "}\n";
    const char* fragShaderCode1 = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "void main() {\n"
                                  "FragColor = vec4(0.0, 0.2, 0.3, 1.0);\n"
                                  "}\n";
    const char* fragShaderCode2 = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "void main() {\n"
                                  "FragColor = vec4(0.5, 0.0, 0.3, 1.0);\n"
                                  "}\n";
    Shader shader1(vertexShaderCode, fragShaderCode1, false);
    Shader shader2(vertexShaderCode, fragShaderCode2, false);

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
        shader1.use();
//        float redValue = (float) sin(glfwGetTime()*10.0f)/2.0f + 0.5f;
//        shader.setFloatV4("aColor", redValue, 0, 0, 1);
        glBindVertexArray(vaoManager2.VAO);
        vaoManager2.drawElements();
        shader2.use();
        glBindVertexArray(vaoManager1.VAO);
        vaoManager1.drawElements();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

TEST(shader, uniform) {
    GLFWwindow* window = createWindow(600, 400, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
            -0.5f, 0.7f, 0.0f,
            0.0f, 0.0f, 0.0f,
            -0.3f, -0.4f, 0.0f
    };
    unsigned int indices[] = {
            0, 1, 2
    };
    VAOManager vaoManager(vertices, sizeof(vertices), indices, sizeof(indices), [](){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
    });
    const char* vertexShaderCode = "#version 330 core\n"
                                   "layout(location = 0) in vec3 aPos;\n"
                                   "void main() {\n"
                                   "gl_Position = vec4(aPos, 1.0);\n"
                                   "}\n";
    const char* fragShaderCode = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "uniform vec4 aColor;"
                                  "void main() {\n"
                                  "FragColor = aColor;\n"
                                  "}\n";
    Shader shader(vertexShaderCode, fragShaderCode, false);

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
        shader.setFloatV4("aColor", redValue, 0, 0, 1);

        glBindVertexArray(vaoManager.VAO);
        vaoManager.drawElements();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}


TEST(check, stb_image) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(R"(D:\Projects\C++\learn_opengl\resources\texture\hutao.jpeg)", &width, &height, &nrChannels, 0);
    std::cout << width << ", " << height << ", " << nrChannels << std::endl;
}

TEST(check, glm) {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << std::endl;
}

TEST(shader, transform) {
    GLFWwindow* window = createWindow(600, 400, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };
    unsigned int indices[] = {
            0, 1, 2,
    };
    VAOManager vaoManager(vertices, sizeof(vertices), indices, sizeof(indices), [](){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    });
    Shader shader(R"(D:\Projects\C++\learn_opengl\resources\shader\transform.vert)",
                  R"(D:\Projects\C++\learn_opengl\resources\shader\transform.frag)");


    auto config_texture = [](unsigned int& texture, const char * filename) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
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
        unsigned char * data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        std::cout << width << ", " << height << std::endl;
    };
    unsigned int texture;
    config_texture(texture, R"(D:\Projects\C++\learn_opengl\resources\texture\hutao.jpeg)");
    // 切记！！！设置uniform之前一定先use();
    shader.use();
    shader.setInt("texture1", 0);
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
        glBindTexture(GL_TEXTURE_2D, texture);
        // transform
        glm::mat4 trans;
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "trans"),
                           1,
                           GL_FALSE,
                           glm::value_ptr(trans));
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

