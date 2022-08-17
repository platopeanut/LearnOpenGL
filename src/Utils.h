#ifndef LEARN_OPENGL_UTILS_H
#define LEARN_OPENGL_UTILS_H

#include "Constants.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

namespace Default {
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window);


    GLFWwindow* createWindow(int width, int height, const char* title);
}




#endif //LEARN_OPENGL_UTILS_H
