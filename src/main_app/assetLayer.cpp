//
// Created by Bob on 08/02/2021.
//

#include "assetLayer.h"

void assetLayer::printIndex(const char *file) {
    FILE* pakFile = fopen(file,"r");
    FILE* encryptionKeyFile = fopen("assets/Packs/packlist.dat","r");
    char* magic = (char*)alloca(sizeof(char)*9);
    magic[8] = '\0';
    fread(magic,sizeof(char),8,pakFile);
    logger::log(logger::INFO, ("The magic in the file is: "+std::string(magic)).c_str(), "Assets");
    if (strcmp(magic,"NadeoPak") == 0) {
        logger::log(logger::INFO, "Magic is correct","Assets");
    }
    else {
        logger::log(logger::FATAL, "File magic is incorrect, please check if the file is not corrupted", "Assets");
    }
    char* encryptionVer = (char*)alloca(sizeof(char)*2);
    encryptionVer[1] = '\0';
    fread(encryptionVer,sizeof(char),1,encryptionKeyFile);
    logger::log(logger::INFO, ("The encryption key file version is: "+std::to_string((int)encryptionVer)).c_str(),"Assets");

}
