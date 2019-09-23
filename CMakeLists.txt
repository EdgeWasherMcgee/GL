cmake_minimum_required(VERSION 2.8)
project(GL)

include_directories("${PROJECT_SOURCE_DIR}/src/")
include_directories("${PROJECT_SOURCE_DIR}/src/objects")
include_directories("${PROJECT_SOURCE_DIR}/src/common")
include_directories("${PROJECT_SOURCE_DIR}/src/shader")

add_library(vao vao.cpp)
add_library(ibo indexBuffer.cpp)
add_library(vbo vertexBuffer.cpp)
add_library(shader shader.cpp)
add_executable(app "App.cpp")
