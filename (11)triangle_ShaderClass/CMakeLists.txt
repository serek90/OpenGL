cmake_minimum_required(VERSION "3.2.1")

project("Shaders")

find_library(GLEW32S glew32s  "glew-2.2.0/lib/Release/x64")
link_directories("C:/glfw-3.3.6.bin.WIN64/lib-vc2019/" "C:/glew-2.1.0/lib/Release/x64")
include_directories("C:/glfw-3.3.6.bin.WIN64/include" "C:/glew-2.1.0/include")

add_executable("${PROJECT_NAME}" "shaders_triangle.cpp" "Shader.h" "Shader.cpp")
target_link_libraries("${PROJECT_NAME}" glfw3 opengl32.lib glew32s)



