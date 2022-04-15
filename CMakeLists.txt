cmake_minimum_required(VERSION 3.21)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/lib-mingw-w64)
link_directories(${PROJECT_SOURCE_DIR}/lib/googletest)

file(GLOB SOURCE_DIR src/*)

add_library(LIB STATIC ${SOURCE_DIR})
target_link_libraries(LIB libglfw3.a)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} LIB)