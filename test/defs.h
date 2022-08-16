#ifndef LEARN_OPENGL_DEFS_H
#define LEARN_OPENGL_DEFS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

// settings
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* createWindow(int width, int height, const char* title);

#endif //LEARN_OPENGL_DEFS_H
