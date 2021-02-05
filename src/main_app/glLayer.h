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

typedef void (APIENTRY *DEBUGPROC)(GLenum source,
                                   GLenum type,
                                   GLuint id,
                                   GLenum severity,
                                   GLsizei length,
                                   const GLchar *message,
                                   const void *userParam);

typedef glm::vec<2,int,glm::defaultp> resolution;

class glLayer {
public:
    glLayer() = delete;
    glLayer(resolution res, std::vector<const char*>* shaders);
    void compileShader(shaderType sType, const char* code);
    void GL_ERROR(GLenum source,
                  GLenum type,
                  GLuint id,
                  GLenum severity,
                  GLsizei length,
                  const GLchar *message,
                  const void *userParam);
};

#endif //REMANIA_GLLAYER_H
