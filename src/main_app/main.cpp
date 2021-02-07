#include "utils.h"
#include "pch.h"
#include "glLayer.h"

int main() {
    const char* vSource = "#version 430\n"
                          "\n"
                          "layout (location=0) in vec3 position;\n"
                          "\n"
                          "uniform mat4 mv_matrix;\n"
                          "uniform mat4 proj_matrix;\n"
                          "\n"
                          "void main()\n"
                          "{\n"
                          "        gl_Position = proj_matrix*mv_matrix*vec4(position,1.0);\n"
                          "}";
    const char* fSource = "#version 430\n"
                          "\n"
                          "out vec4 color;\n"
                          "\n"
                          "uniform mat4 mv_matrix;\n"
                          "uniform mat4 proj_matrix;\n"
                          "\n"
                          "void main() {\n"
                          "        color = vec4(1.0,0.0,0.0,1.0);\n"
                          "}";
    std::vector<shader> shaderSet = {shader{vertex,vSource},shader{fragment,fSource}};
    std::vector<const char*> names = {"Shader 1"};
    glLayer layer = glLayer(resolution{800,600},NULL,&shaderSet,&names,"Hello World",0);
    GLuint vbo = layer.genVBO();
    float vertexPositions[108] = {
            -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
            1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
            1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
    };
    layer.setVBO(vbo,sizeof(vertexPositions),vertexPositions);
    while (true) {
        layer.addInstruction(glInstruction{
                "Shader 1",
                vbo,
                0, 36,
                GL_TRIANGLES,
                glm::vec3(0.0f, -2.0f, 0.0f)
        });
        layer.update();
    }
    return 0;
}
