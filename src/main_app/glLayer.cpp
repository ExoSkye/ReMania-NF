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
                    log::log(log::WARN,message,"OpenGL");
                    break;
                case GL_DEBUG_TYPE_ERROR:
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    log::log(log::ERROR,message,"OpenGL",__FILE__,__LINE__);
                    break;
                default:
                    log::log(log::INFO,message,"OpenGL");
                    break;
            }
            break;
        default:
            break;
    }
}

glLayer::glLayer(resolution res, std::vector<const char*>* shaderSet) {
    if (!glfwInit()) {
        log::log(log::FATAL,"glfwInit() returned non 0 value","Engine",__FILE__,__LINE__);
    }

}

void glLayer::compileShader(shaderType sType, const char *code) {

}
