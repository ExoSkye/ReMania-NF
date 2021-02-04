//
// Created by protobit on 04/02/2021.
//

#ifndef TMNF_REMAKE_UTILS_H
#define TMNF_REMAKE_UTILS_H

#include <cstdio>

namespace log {
    bool verbose = false;

    enum type {
        VERBOSE,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    void log(type logType, char* logMsg, char* file="\0", int line=0);
}

#endif //TMNF_REMAKE_UTILS_H
