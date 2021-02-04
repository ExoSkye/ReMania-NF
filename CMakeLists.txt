cmake_minimum_required(VERSION 3.19)
project(ReMania)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 4.0 REQUIRED)

add_subdirectory(lib/glew/)
add_subdirectory(lib/glfw3)

file(GLOB_RECURSE TMNF_FILES
        ${CMAKE_SOURCE_DIR}/src/main_app/*.c
        ${CMAKE_SOURCE_DIR}/src/main_app/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main_app/*.h
        ${CMAKE_SOURCE_DIR}/src/main_app/*.hpp)

add_executable(ReMania ${TMNF_FILES})
target_link_libraries(ReMania glfw libglew_static)
target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include)
