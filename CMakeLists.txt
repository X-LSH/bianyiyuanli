# cmake_minimum_required(VERSION <specify CMake version here>)
project(untitled6)

link_directories("C:/Program Files/MinGW/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D FREEGLUT_STATIC")

add_executable(untitled6 main.cpp)
#target_link_libraries(untitled6 -lopengl32 -lglut32 -lglu32)
