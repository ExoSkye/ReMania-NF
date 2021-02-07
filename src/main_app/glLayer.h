//
// Created by Bob on 05/02/2021.
//

#ifndef REMANIA_GLLAYER_H
#define REMANIA_GLLAYER_H

#ifndef CALLBACK
#define CALLBACK
#endif

#include "pch.h"
#include "utils.h"

enum shaderType {
    vertex,
    fragment,
};

struct shader {
    shaderType sType;
    const char* sSource;
};

typedef glm::vec<2,int,glm::defaultp> resolution;

struct glInstruction {
    const char* shaderName;
    GLuint vbo;
    int start, len;
    GLenum type;
    glm::vec3 position;
};


class glLayer {
    std::mutex instruction_mutex;
    std::queue<glInstruction> instructions;
    GLFWwindow *window;
    std::unordered_map<const char*,std::vector<glInstruction>> shaderMap;
    std::unordered_map<std::string,GLuint> programs;
    GLuint vao;
    GLuint mvLoc, projLoc;
    float aspect;
    int width, height, newWidth, newHeight;
    glm::mat4 pMat, vMat, mMat, mvMat;
public:
    glm::vec3 cameraLocation;
    glLayer() = delete;
    glLayer(resolution res, GLFWmonitor *target_monitor, std::vector<shader> *shaderSet, std::vector<const char*>* programNames, const char *name,
            int swapInterval);

    ~glLayer();

    GLuint compileShader(shaderType sType, const char* code);
    GLuint linkProgram(GLuint Shader1, GLuint Shader2);
    static void GL_ERROR(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam);

    void WINDOW_RESHAPE_CALLBACK(GLFWwindow*,int newWidth,int newHeight);

    void addInstruction(glInstruction inst);
    bool update();
    GLuint genVBO();
    static void setVBO(GLuint vbo, int len, void* data);
};

#endif //REMANIA_GLLAYER_H
