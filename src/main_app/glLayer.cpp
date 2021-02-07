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
    logger::log(logger::VERBOSE,"Initializing","OpenGL");
    TracyCZoneNC(glLayerInit,"OpenGL Layer Initialization",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    TracyCZoneNC(glfwInitZone,"Initialize GLFW",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    if (!glfwInit()) {
        logger::log(logger::FATAL, "glfwInit() returned a value other than 0", "OpenGL", __FILE__, __LINE__);
    }
    TracyCZoneNC(windowInit,"Create GLFW Window",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(res.x, res.y, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    TracyCZoneEnd(windowInit);
    TracyCZoneEnd(glfwInitZone);
    TracyCZoneNC(glewInitZone,"Initialize GLEW",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    if(glewInit() != GLEW_OK) {
        logger::log(logger::FATAL, "glewInit() returned a value other than GLEW_OK", "OpenGL", __FILE__, __LINE__);
    }
    TracyCZoneEnd(glewInitZone);
    glfwSwapInterval(swapInterval);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glLayer::GL_ERROR, 0);
    glGenVertexArrays(1, &vao);
    TracyCZoneNC(shaderComp,"Compile Shaders",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    assert(shaderSet->size()/2 == programNames->size());

    for (int i = 0; i < shaderSet->size(); i+=2) {
        GLuint shader1 = compileShader(shaderSet->at(i).sType,shaderSet->at(i).sSource);
        GLuint shader2 = compileShader(shaderSet->at(i+1).sType,shaderSet->at(i+1).sSource);
        GLuint program = linkProgram(shader1,shader2);

        programs[std::string(programNames->at(i/2))] = program;


    }
    TracyCZoneEnd(shaderComp)
    TracyCZoneEnd(glLayerInit);
}

GLuint glLayer::compileShader(shaderType sType, const char *code) {
    TracyCZoneNC(shaderComp,"Compile a shader",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    GLuint shader = glCreateShader(sType == fragment ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);
    glShaderSource(shader,1,&code,NULL);
    glCompileShader(shader);
    TracyCZoneEnd(shaderComp)
    return shader;
}

GLuint glLayer::linkProgram(GLuint Shader1, GLuint Shader2) {
    TracyCZoneNC(shaderLink,"Link 2 shaders",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    GLuint program = glCreateProgram();
    glAttachShader(program,Shader1);
    glAttachShader(program,Shader2);
    glLinkProgram(program);
    TracyCZoneEnd(shaderLink)
    return program;
}

void glLayer::addInstruction(glInstruction inst) {
    TracyCZoneNC(glInstructionAdd,"Add OpenGL Instruction to the queue",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    instruction_mutex.lock();
    instructions.emplace(inst);
    instruction_mutex.unlock();
    TracyCZoneEnd(glInstructionAdd);
}

bool glLayer::update() {
    TracyCZoneNC(update,"Update screen",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    TracyCZoneNC(cameraMatrix,"Work out camera projection matrix",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    vMat = glm::translate(glm::mat4(1.0f),-cameraLocation);
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0427f, aspect,0.1f,1000.0f);
    TracyCZoneEnd(cameraMatrix);
    TracyCZoneNC(sortShaders,"Sort instructions by used shader",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    shaderMap.clear();
    while (instructions.size() > 0) {
        instruction_mutex.lock();
        glInstruction inst = instructions.front();
        shaderMap[inst.shaderName].emplace_back(inst);
        instructions.pop();
        instruction_mutex.unlock();
    }
    TracyCZoneEnd(sortShaders);
    for(const auto& pair : shaderMap) {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programs[pair.first]);
        mvLoc = glGetUniformLocation(programs[pair.first],"mv_matrix");
        projLoc = glGetUniformLocation(programs[pair.first],"proj_matrix");
        for (auto inst : pair.second) {
            TracyCZoneNC(modelMatrix,"Work out model matrix",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
            mMat = glm::translate(glm::mat4(1.0f),inst.position);
            mvMat = vMat*mMat;
            TracyCZoneEnd(modelMatrix)
            TracyCZoneNC(openglrender,"Run shader and render",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
            glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvMat));
            glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(pMat));
            glBindBuffer(GL_ARRAY_BUFFER,inst.vbo);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(0);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDrawArrays(inst.type,inst.start,inst.len);
            TracyCZoneEnd(openglrender);
        }
    }
    TracyCZoneNC(glfwSwapandPoll,"GLFW Swap buffers and poll events",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering)
    glfwSwapBuffers(window);
    glfwPollEvents();
    TracyCZoneEnd(glfwSwapandPoll);
    TracyCZoneEnd(update);
    FrameMark;
    return glfwWindowShouldClose(window);
}

glLayer::~glLayer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLuint glLayer::genVBO() {
    TracyCZoneNC(genVBOzone,"Generate VBO",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    GLuint vbo;
    glBindVertexArray(vao);
    glGenBuffers(1,&vbo);
    TracyCZoneEnd(genVBOzone);
    return vbo;
}

void glLayer::setVBO(GLuint vbo, int len, void *data) {
    TracyCZoneNC(setVBOzone,"Set VBO with data",TRACY_OPENGL_COLOUR,SUBSYSTEMS & Sys_Rendering);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,len,data,GL_STATIC_DRAW);
    TracyCZoneEnd(setVBOzone);
}
