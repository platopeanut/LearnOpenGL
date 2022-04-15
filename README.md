# OpenGL Learning Template

> *Author: Peanut*  
> *LastUpdate: 2022/4/15*

[TOC]


## Environmental requirements

- MinGW
- CMake
- x64

## Dependencies

> *If the following dependent libraries encounter problems when building the project, please refer to this [link](https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/)*

- [GLFW](https://www.glfw.org/download.html)
- [GLAD](https://glad.dav1d.de/)

> *How to check opengl version?*  
> **Linux:** `glxinfo`  
> **Windows:** [OpenGL Extension Viewer](https://download.cnet.com/OpenGL-Extensions-Viewer/3000-18487_4-34442.html) 
- OpenGL 3.3+[CORE_PROFILE]

## Build & Run
~~~shell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make # if windows, run: mingw32-make
./opengl_demo
~~~


