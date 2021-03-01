cmake_minimum_required(VERSION 3.11)
project(ReMania CXX)

option(TESTS "Turn tests on" ON)

set(CMAKE_CXX_STANDARD 20)

# Find OpenGL, GLEW and GLFW3
find_package(OpenGL 4.3 REQUIRED)
find_package(GLEW 1.9)
find_package(glfw3)

# Options/Overrides for libraries (eg only building shared libraries)
option(TRACY "Enables the Tracy profiler support" OFF)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the shared glfw library")
set(glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library")
set(ONLY_LIBS ON CACHE BOOL "Only build glew library")
set(ENABLE_STATIC OFF CACHE BOOL "Build static LZO library.")
set(ENABLE_SHARED ON CACHE BOOL "Build shared LZO library.")
set(ENABLE_PROGRAMS OFF CACHE BOOL "Build mbed TLS programs.")
set(ENABLE_TESTING OFF CACHE BOOL "Build mbed TLS tests.")

# Configure all the libs
if (NOT GLEW_FOUND)
        add_subdirectory(lib/glew)
endif()
if (NOT glfw3_FOUND)
        add_subdirectory(lib/glfw3)
endif()
add_subdirectory(lib/lzo)
add_subdirectory(lib/mbedtls)

include(CTest)

if (TESTS MATCHES ON)
    enable_testing()
    include(tests/tests.cmake)
endif()

set(PREFIX src/main_app)
add_executable(ReMania ${PREFIX}/assetLayer.cpp ${PREFIX}/engine.cpp ${PREFIX}/glLayer.cpp ${PREFIX}/main.cpp ${PREFIX}/utils.cpp tracy/TracyClient.cpp src/main_app/physics.cpp src/main_app/physics.h)
target_link_libraries(ReMania glfw mbedtls ${OPENGL_LIBRARIES})

if (NOT GLEW_FOUND)
        target_link_libraries(ReMania libglew_shared)
else()
        target_link_libraries(ReMania ${GLEW_LIBRARIES})
endif()

target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include lib/glm tracy lib/lzo/include lib/mbedtls/include lib/fsx)
if (TRACY MATCHES ON)
    target_compile_definitions(ReMania PUBLIC TRACY_ENABLE)
endif()
if (UNIX)
    target_link_libraries(ReMania pthread dl)
endif()

set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/out/)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:ReMania> ${CMAKE_BINARY_DIR}/out/)
if(NOT GLFW3_FOUND)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:glfw> ${CMAKE_BINARY_DIR}/out/)
endif()
if (NOT GLEW_FOUND)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:libglew_shared> ${CMAKE_BINARY_DIR}/out/)
endif()
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/out/assets)
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/out/assets)
