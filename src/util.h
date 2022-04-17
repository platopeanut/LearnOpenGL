#ifndef LEARN_OPENGL_UTIL_H
#define LEARN_OPENGL_UTIL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* createWindow(int width, int height, const char* title);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif //LEARN_OPENGL_UTIL_H
