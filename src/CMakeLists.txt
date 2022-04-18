project(MY_LIB)

file(GLOB SOURCE_DIR third_party/* ./*)
add_library(${PROJECT_NAME} STATIC ${SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} libglfw3.a)
