#include "utils.h"
#include "pch.h"
#include "glLayer.h"

int main() {
    const char* vSource =
            "#version 430\n"
            "void main()\n"
            "{ gl_Position = vec4(0.0,0.0,0.0,1.0); };";
    const char* fSource =
            "#version 430\n"
            "void main()\n"
            "{ color = vec4(0.0,0.0,1.0,1.0); };";
    std::vector<shader> shaderSet = {shader{vertex,vSource},shader{fragment,fSource}};
    std::vector<const char*> names = {"Shader 1"};
    glLayer(resolution{800,600},NULL,&shaderSet,&names,"Hello World",0);
    return 0;
}
