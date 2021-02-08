cmake_minimum_required(VERSION 3.10)
project(iAlgorithm)

file(GLOB_RECURSE IALGO_FILES
        iAlgorithm/i*.cpp
        iAlgorithm/i*.h)

add_library(iAlgorithm SHARED ${IALGO_FILES})