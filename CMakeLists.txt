cmake_minimum_required(VERSION 3.19)
project(ReMania)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 4.3 REQUIRED)

option(TRACY "Enables the Tracy profiler support" OFF)

set(PLATFORM "ReMania-NF" CACHE STRING "Platform selection (affects output executable name, used for CI artifacts)")

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the shared glfw library")
set(glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library")
set(ONLY_LIBS ON CACHE BOOL "Only build glew library")
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw3)
add_subdirectory(lib/lzokay)

file(GLOB_RECURSE RMNF_FILES
        ${CMAKE_SOURCE_DIR}/src/main_app/*.c
        ${CMAKE_SOURCE_DIR}/src/main_app/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main_app/*.h
        ${CMAKE_SOURCE_DIR}/src/main_app/*.hpp)

add_executable(ReMania ${RMNF_FILES} tracy/TracyClient.cpp)
target_link_libraries(ReMania glfw libglew_shared lzokay)
set_target_properties(ReMania PROPERTIES OUTPUT_NAME ${PLATFORM})
target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include lib/glm tracy lib/lzokay lib/iAlgorithm)
if (TRACY MATCHES ON)
    target_compile_definitions(ReMania PUBLIC TRACY_ENABLE)
endif()
if (UNIX)
    target_link_libraries(ReMania pthread dl)
endif()
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/out/)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:ReMania> ${CMAKE_BINARY_DIR}/out/)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:glfw> ${CMAKE_BINARY_DIR}/out/)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:libglew_shared> ${CMAKE_BINARY_DIR}/out/)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/out/assets)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/out/assets)
