#include "./src/Shader.h"
#include "./src/VAOManager.h"
#include "./src/util.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
float yaw = 0;
float pitch = 0;

bool firstMouse = true;

float fov = 45.0f;

int main() {
    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL Main");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 隐藏光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 鼠标回调函数
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x_pos, double y_pos){
        if (firstMouse) {
            lastX = (float) x_pos;
            lastY = (float) y_pos;
            firstMouse = false;
        }
        float x_offset = (float) x_pos - lastX;
        float y_offset = lastY - (float) y_pos;
        lastX = (float) x_pos;
        lastY = (float) y_pos;
        float sensitivity = 0.05f;
        x_offset *= sensitivity;
        y_offset *= sensitivity;
        yaw += x_offset;
        pitch += y_offset;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        glm::vec3 front;
        front.x = (float) (cos(glm::radians(pitch)) * cos(glm::radians(yaw)));
        front.y = (float) (sin(glm::radians(pitch)));
        front.z = (float) (cos(glm::radians(pitch)) * sin(glm::radians(yaw)));
        cameraFront = glm::normalize(front);
    });
    // 鼠标滚轮回调函数
    glfwSetScrollCallback(window, [](GLFWwindow* window, double x_offset, double  y_offset){
        if (fov >= 1.0f && fov <= 45.0f)
            fov -= (float) y_offset;
        if (fov <= 1.0f)
            fov = 1.0f;
        if (fov >= 45.0f)
            fov = 45.0f;
    });
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    VAOManager vaoManager(vertices, sizeof(vertices), [](){
        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        // color
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(1);
        // texture coordinate
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
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
    // transform
    glm::mat4 model;
    // camera
    glm::mat4 view;
    glm::mat4 projection;
//    shader.setFloatM4("view", view);
//    shader.setFloatM4("projection", projection);
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        // draw
        shader.use();
        glBindVertexArray(vaoManager.VAO);
        // transform
        view = glm::lookAt(
                cameraPos,//position
                cameraPos + cameraFront,//target
                cameraUp);//up direction
        projection = glm::perspective(glm::radians(fov), (float) SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
        shader.setFloatM4("projection", projection);
        shader.setFloatM4("view", view);
        for (const auto &item: cubePositions) {
            glm::mat4 tmpModel = glm::translate(model, glm::vec3(item[0], item[1], item[2]));
            shader.setFloatM4("model", tmpModel);
            vaoManager.drawArrays();
        }
//        model = glm::rotate(model, (float) (sin(glfwGetTime()) * 0.1), glm::vec3(0.0f, 1.0f, 0.0f));
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

float deltaTime = 0.0f;
float lastTime = 0.0f;
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    auto currentTime = (float) glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
}

