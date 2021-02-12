#ifndef PCH_INCLUDED
#define PCH_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cassert>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <unordered_map>
#include <Tracy.hpp>
#include <TracyC.h>
#include <queue>
#include <mutex>
#include <string>
#include <mbedtls/md5.h>
#include <mbedtls/blowfish.h>
#include <mbedtls/config.h>
#include <lzo/lzo1x.h>
#include <bitset>
#include <memory>

#define TRACY_OPENGL_COLOUR 0xff7f00
#define TRACY_ENGINE_COLOUR 0xff0000
#define TRACY_PHYSICS_COLOUR 0x0000ff
#define TRACY_GAME_LOGIC_COLOUR 0x00ff00

enum SubSystems {
    Sys_Physics = 1 << 0,
    Sys_Rendering = 1 << 1,
    Sys_GameLogic = 1 << 2,
    Sys_Engine = 1 << 3,
};

#define SUBSYSTEMS Sys_Physics | Sys_Rendering | Sys_GameLogic | Sys_Engine

#endif
