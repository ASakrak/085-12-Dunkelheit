//test
cmake_minimum_required(VERSION 3.10)

project(Master085-12)
add_executable(Master085-12 main.cpp)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

add_dependencies(testas OpenGL::OpenGL)
include_directories(${GLUT_INCLUDE_DIRS} )

target_link_libraries(testas OpenGL::OpenGL ${GLUT_LIBRARY} 