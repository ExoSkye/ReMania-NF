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

glLayer::glLayer(resolution res, GLFWmonitor* target_monitor , std::vector<shader>* shaderSet, std::vector<const char*>* programNames, const char* name, int swapInterval) {
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

    assert(shaderSet->size()/2 == programNames->size());

    for (int i = 0; i < shaderSet->size(); i+=2) {
        GLuint shader1 = compileShader(shaderSet->at(i).sType,shaderSet->at(i).sSource);
        GLuint shader2 = compileShader(shaderSet->at(i+1).sType,shaderSet->at(i+1).sSource);
        GLuint program = linkProgram(shader1,shader2);
        programs[std::string(programNames->at(i/2))] = program;
    }
}
GLuint glLayer::compileShader(shaderType sType, const char *code) {
    GLuint shader = glCreateShader(sType == fragment ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);
    glShaderSource(shader,1,&code,NULL);
    glCompileShader(shader);
    return shader;
}

GLuint glLayer::linkProgram(GLuint Shader1, GLuint Shader2) {
    GLuint program = glCreateProgram();
    glAttachShader(program,Shader1);
    glAttachShader(program,Shader2);
    glLinkProgram(program);
    return program;
}
