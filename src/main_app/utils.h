//
// Created by protobit on 04/02/2021.
//

#ifndef TMNF_REMAKE_UTILS_H
#define TMNF_REMAKE_UTILS_H

#include "pch.h"

namespace logger {
    inline bool verbose = false;

    enum type {
        VERBOSE,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    void log(type logType, const char* logMsg, const char* area);
    void log(type logType, const char* logMsg, const char* area, const char* file, int line);
}

void* operator new(std::size_t count);

void operator delete(void* ptr) noexcept;

#endif //TMNF_REMAKE_UTILS_H
