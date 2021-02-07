#ifndef PCH_INCLUDED
#define PCH_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cassert>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <unordered_map>
#include <Tracy.hpp>
#include <TracyC.h>
#include <queue>
#include <mutex>

#define TRACY_OPENGL_COLOUR 0xff7f00
#define TRACY_ENGINE_COLOUR 0xff0000
#define TRACY_PHYSICS_COLOUR 0x0000ff
#define TRACY_GAME_LOGIC_COLOUR 0x00ff00

enum SusSystems {
    Sys_Physics = 1 << 0,
    Sys_Rendering = 1 << 1,
    Sys_GameLogic = 1 << 2
};

#define SUBSYSTEMS Sys_Physics | Sys_Rendering | Sys_GameLogic

#endif
