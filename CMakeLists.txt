cmake_minimum_required(VERSION 3.21)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/lib-mingw-w64)
link_directories(${PROJECT_SOURCE_DIR}/lib/googletest)


add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} MY_LIB)