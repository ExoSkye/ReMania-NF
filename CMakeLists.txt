cmake_minimum_required(VERSION 3.19)
project(ReMania)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 4.3 REQUIRED)

set(PLATFORM "ReMania-NF" CACHE STRING "Platform selection (affects output executable name, used for CI artifacts)")

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the shared glfw library")
set(glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library")
set(ONLY_LIBS ON CACHE BOOL "Only build glew library")
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw3)
#add_subdirectory(lib/glm)

file(GLOB_RECURSE TMNF_FILES
        ${CMAKE_SOURCE_DIR}/src/main_app/*.c
        ${CMAKE_SOURCE_DIR}/src/main_app/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main_app/*.h
        ${CMAKE_SOURCE_DIR}/src/main_app/*.hpp)

add_executable(ReMania ${TMNF_FILES})
target_link_libraries(ReMania glfw libglew_shared)
set_target_properties(ReMania PROPERTIES OUTPUT_NAME ${PLATFORM})
target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include lib/glm)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/out/)
if(WIN32)
    include(installWin32.cmake)
elseif(UNIX)
    if(APPLE)
    include(installApple.cmake)
    ELSE()
    include(installLinux.cmake)
    ENDIF()
ENDIF()