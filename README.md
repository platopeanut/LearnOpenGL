# OpenGL Learning Template

> *Author: Peanut*  
> *LastUpdate: 2022/4/15*

## Environmental requirements

- MinGW
- CMake
- x64

## Dependencies

> *If the following dependent libraries encounter problems when building the project, please refer to this [link](https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/)*
> *If GoogleTest did not work, Please refer to [Build GoogleTest](#build_google_test)below.*
- [GLFW](https://www.glfw.org/download.html)
- [GLAD](https://glad.dav1d.de/)
- GoogleTest

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

## Build GoogleTest
<a id="build_google_test"></a>

1. Download the latest [release](https://github.com/google/googletest/releases)
2. Unzip the file & Enter the directory
3. Execute the following commands
~~~shell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make # if windows, run: mingw32-make
~~~
4. In`/build/lib` will generate 4 files
   
    - libgmock.a
    - libgmock_main.a
    - libgtest.a
    - libgtest_main.a