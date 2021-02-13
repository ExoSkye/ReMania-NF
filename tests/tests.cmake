set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

file(GLOB files "tests/test_*.cpp")
file(GLOB libFiles "src/main_app/*.cpp")
add_library(testLib STATIC ${libFiles})
target_include_directories(testLib PUBLIC src/main_app lib/glew/include lib/glfw3/include lib/glm tracy lib/lzo/include lib/mbedtls/include)
if (NOT GLEW_FOUND)
        target_link_libraries(testLib glfw libglew_shared mbedtls)
else()
        target_link_libraries(testLib glfw ${GLEW_LIBRARIES} mbedtls)
endif()

foreach(file ${files})
        string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
        add_executable(${file_without_ext} ${file})
        target_link_libraries(${file_without_ext} testLib)
        target_include_directories(${file_without_ext} PUBLIC src/main_app lib/glew/include lib/glfw3/include lib/glm tracy lib/lzo/include lib/mbedtls/include lib/endian/include)
        if(IS_BIG_ENDIAN)
                target_compile_definitions(ReMania __BIG_ENDIAN__)
        endif()
        add_test(${file_without_ext} ${CMAKE_BINARY_DIR}/tests/${file_without_ext} ${CMAKE_BINARY_DIR}/out)
        set_tests_properties(${file_without_ext}
                PROPERTIES
                PASS_REGULAR_EXPRESSION "Test passed")
        set_tests_properties(${file_without_ext}
                PROPERTIES
                FAIL_REGULAR_EXPRESSION "(Exception|Test failed)")
        set_tests_properties(${file_without_ext}
                PROPERTIES
                TIMEOUT 120)
endforeach()
