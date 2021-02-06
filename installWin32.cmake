add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ReMania-NF.exe"
        ${CMAKE_BINARY_DIR}/out/)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_custom_command(TARGET ReMania POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/glew/bin/${CMAKE_BUILD_TYPE}/glewd.dll"
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/out/)
else()
    add_custom_command(TARGET ReMania POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/glew/bin/${CMAKE_BUILD_TYPE}/glew.dll"
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/out/)
endif()
add_custom_command(TARGET ReMania POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/lib/glfw3/src/${CMAKE_BUILD_TYPE}/glfw3.dll"
        ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/out/)