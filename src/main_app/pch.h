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

#include <climits>

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}


#define TRACY_OPENGL_COLOUR 0xff7f00
#define TRACY_ENGINE_COLOUR 0xff0000
#define TRACY_PHYSICS_COLOUR 0x0000ff
#define TRACY_GAME_LOGIC_COLOUR 0x00ff00

#ifdef __BIG_ENDIAN__
#   define makeLE(T,u) swap_endian<T>(u)
#else
#   define makeLE(T,u) u 
#endif

enum SubSystems {
    Sys_Physics = 1 << 0,
    Sys_Rendering = 1 << 1,
    Sys_GameLogic = 1 << 2,
    Sys_Engine = 1 << 3,
};

#define SUBSYSTEMS Sys_Physics | Sys_Rendering | Sys_GameLogic | Sys_Engine

#endif
