project(learn_opengl_test)

enable_testing()
file(GLOB TEST_DIR ./*)
add_executable(${PROJECT_NAME} ${TEST_DIR})
target_link_libraries(${PROJECT_NAME}
        LIB
        libglfw3.a
        libgtest.a
        libgtest_main.a
)