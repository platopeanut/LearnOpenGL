cmake_minimum_required(VERSION 3.23)
project(LEARN_OPENGL_TEST)

enable_testing()
file(GLOB TEST_DIR ./**/* ./*)
add_executable(${PROJECT_NAME} ${TEST_DIR})
target_link_libraries(${PROJECT_NAME}
        LEARN_OPENGL_SRC
        libglfw3.a
        libgtest.a
        libgtest_main.a
)