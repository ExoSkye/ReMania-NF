//
// Created by Bob on 05/02/2021.
//

#include "glLayer.h"

void glLayer::GL_ERROR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                       const void *userParam) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            switch (type) {
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    logger::log(logger::WARN, message, "OpenGL");
                    break;
                case GL_DEBUG_TYPE_ERROR:
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    logger::log(logger::ERROR, message, "OpenGL", __FILE__, __LINE__);
                    break;
                default:
                    logger::log(logger::INFO, message, "OpenGL");
                    break;
            }
            break;
        default:
            break;
    }
}

glLayer::glLayer(resolution res, GLFWmonitor* target_monitor , std::vector<shader>* shaderSet, const char* name, int swapInterval) {
    if (!glfwInit()) {
        logger::log(logger::FATAL, "glfwInit() returned a value other than 0", "OpenGL", __FILE__, __LINE__);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(res.x, res.y, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK) {
        logger::log(logger::FATAL, "glewInit() returned a value other than GLEW_OK", "OpenGL", __FILE__, __LINE__);
    }
    glfwSwapInterval(swapInterval);
#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glLayer::GL_ERROR, 0);  
#endif

}
void glLayer::compileShader(shaderType sType, const char *code) {

}
