add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/ReMania-NF"
        ${CMAKE_BINARY_DIR}/out/)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_custom_command(TARGET ReMania POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/glew/lib/libglewd.dylib"
            ${CMAKE_BINARY_DIR}/out/)
else()
    add_custom_command(TARGET ReMania POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/glew/lib/libglew.dylib"
            ${CMAKE_BINARY_DIR}/out/)
endif()
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/lib/glfw3/src/libglfw.dylib"
        ${CMAKE_BINARY_DIR}/out/)