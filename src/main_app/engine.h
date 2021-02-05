//
// Created by Bob on 05/02/2021.
//

#ifndef REMANIA_ENGINE_H
#define REMANIA_ENGINE_H

#include "pch.h"
#include "utils.h"
#include "glLayer.h"

class engine {

    std::vector<std::string> LowShaders;
    std::vector<std::string> MedShaders;
    std::vector<std::string> HigeShaders;
    std::vector<std::string> UltShaders;
    std::vector<std::function<void(double,glLayer*)>> onFrameStart;
    std::vector<std::function<void(double,glLayer*)>> onFrameEnd;
    engine(std::vector<std::string>* ShaderSet);
};

#endif //REMANIA_ENGINE_H
