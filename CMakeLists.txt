cmake_minimum_required(VERSION 3.19)
project(ReMania)

set(CMAKE_CXX_STANDARD 20)

# Find OpenGL
find_package(OpenGL 4.3 REQUIRED)

# Get OpenSSL
add_subdirectory(lib/openssl-cmake)

# Options/Overrides for libraries (eg only building shared libraries)
option(TRACY "Enables the Tracy profiler support" OFF)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build the shared glfw library")
set(glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library")
set(ONLY_LIBS ON CACHE BOOL "Only build glew library")
set(ENABLE_STATIC OFF CACHE BOOL "Build static LZO library.")
set(ENABLE_SHARED ON CACHE BOOL "Build shared LZO library.")

# Configure all the libs
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw3)
add_subdirectory(lib/lzo)

set(PREFIX src/main_app)
add_executable(ReMania ${PREFIX}/assetLayer.cpp ${PREFIX}/engine.cpp ${PREFIX}/glLayer.cpp ${PREFIX}/main.cpp ${PREFIX}/utils.cpp tracy/TracyClient.cpp)
target_link_libraries(ReMania glfw libglew_shared crypto)

target_include_directories(ReMania PUBLIC lib/glew/include lib/glfw3/include lib/glm tracy lib/lzo/include)
if (TRACY MATCHES ON)
    target_compile_definitions(ReMania PUBLIC TRACY_ENABLE)
endif()
if (UNIX)
    target_link_libraries(ReMania pthread dl)
endif()
if(WIN32) 
    target_link_libraries(ReMania crypt32) 
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
