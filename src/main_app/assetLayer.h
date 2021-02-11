//
// Created by Bob on 08/02/2021.
//

#ifndef REMANIA_ASSETLAYER_H
#define REMANIA_ASSETLAYER_H

#include "pch.h"
#include "utils.h"

#define readFileWithDecl(file,pos,len,varname,vartype) \
vartype varname;                                       \
readFile(file,pos,len,varname)

#define readFile(file,pos,len,varname) \
file.seekg(pos);                                       \
file.read((char*)&varname,len);

class assetLayer {
public:
    void printIndex(const char* file);
    uint32_t getSalt(std::ifstream& file);
    uint8_t getPackListVer(std::ifstream& file);
    uint8_t getNumPaks(std::ifstream& file);
    std::string getName(uint8_t index, uint32_t salt, std::ifstream& file);
    std::string getKey(uint8_t index, uint32_t salt, const char* name, std::ifstream& file);
    long getIndexStart(uint8_t index, std::ifstream& file);
    std::string getMagic(std::ifstream& file);
};

#endif //REMANIA_ASSETLAYER_H
