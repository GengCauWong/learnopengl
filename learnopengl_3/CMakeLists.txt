cmake_minimum_required(VERSION 3.18)
project(learnopengl_3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(${PROJECT_NAME} main.cpp glad/glad.c Shader.cpp Shader.h )

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})

