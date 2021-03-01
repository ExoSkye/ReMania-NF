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

enum nodeType {
    File,
    Folder
};

struct FolderDesc {
    uint32_t parentFolderIndex;
    std::string name;
};

struct FileDesc {
    uint32_t folderIndex; // index into folders
    std::string name;
    uint32_t unknown;
    uint32_t uncompressedSize;
    uint32_t compressedSize;
    uint32_t offset;
    uint32_t classID; // indicates the type of the file
    uint64_t flags;
};

namespace assetLayer {
    void printIndex(const char* file);
    uint32_t getSalt(std::ifstream& file);
    uint8_t getPackListVer(std::ifstream& file);
    uint8_t getNumPaks(std::ifstream& file);
    std::string getName(uint8_t index, uint32_t salt, std::ifstream& file);
    std::string getKey(uint8_t index, uint32_t salt, const char* name, std::ifstream& file);
    long getIndexStart(uint8_t index, std::ifstream& file);
    std::string getMagic(std::ifstream& file);
    uint32_t getPackVer(std::ifstream& file);
    std::string getHeaderIV(std::ifstream& file);
    std::string decryptBlowfish(std::string& data, char* key, char* IV);
    uint64_t CalcIVXor(uint64_t ivXor, char* pInput, int count);
    void extractPaks();
};

#endif //REMANIA_ASSETLAYER_H
