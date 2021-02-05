cmake_minimum_required(VERSION 3.19)
project(ReMania)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 4.3 REQUIRED)

set(PLATFORM "ReMania-NF" CACHE STRING "Platform selection (affects output executable name, used for CI artifacts)")

set(BUILD_SHARED_LIBS ON)
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw3)
add_subdirectory(lib/glm)

file(GLOB_RECURSE TMNF_FILES
        ${CMAKE_SOURCE_DIR}/src/main_app/*.c
        ${CMAKE_SOURCE_DIR}/src/main_app/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main_app/*.h
        ${CMAKE_SOURCE_DIR}/src/main_app/*.hpp)

add_executable(ReMania ${TMNF_FILES})
target_link_libraries(ReMania glfw libglew_shared glm_shared)
set_target_properties(ReMania PROPERTIES OUTPUT_NAME ${PLATFORM})
target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include lib/glm)
