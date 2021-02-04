//
// Created by protobit on 04/02/2021.
//

#include "utils.h"

void log::log(type logType, char *logMsg, char *file = "\0", int line = 0) {
    switch (logType) {
        case VERBOSE:
            if (verbose) {
                printf("[VERBOSE] %s",logMsg);
            }
            break;
        case INFO:
            printf("[INFO] %s",logMsg);
            break;
        case WARN:
            printf("[WARN] %s",logMsg);
            break;
        case ERROR:
            printf("[ERROR] %s at %s:%i",logMsg,file,line);
            break;
        case FATAL:
            printf("[FATAL ERROR] %s at %s:%i",logMsg,file,line);
            break;
    }
}