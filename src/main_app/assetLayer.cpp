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

    uint8_t encryptionVer = 0;
    fread(&encryptionVer,sizeof(uint8_t),1,encryptionKeyFile);
    logger::log(logger::INFO, ("The encryption key file version is: "+std::to_string(encryptionVer)).c_str(),"Assets");

    // Adapted code from https://wiki.xaseco.org/wiki/Packlist.dat

    uint8_t numPacks = 0;
    fread(&numPacks,sizeof(uint8_t),1,encryptionKeyFile);

    uint32_t salt = 0;
    fseek(encryptionKeyFile,sizeof(uint32_t),SEEK_CUR);
    fread(&salt,sizeof(uint32_t),1,encryptionKeyFile);

    MD5_CTX c;
    MD5_Init(&c);

    char* nameKeyString = (char*)alloca(32*sizeof(char)+sizeof(uint32_t));
    sprintf(nameKeyString,"6611992868945B0B59536FC3226F3FD0%u", salt);

    MD5_Update(&c,nameKeyString,32*sizeof(char)+sizeof(uint32_t));
    auto* nameKey = (unsigned char*)alloca(16*sizeof(char));
    MD5_Final(nameKey, &c);

    std::unordered_map<std::string,std::string> packs;

    char* name = (char*)alloca(33*sizeof(char));
    name[32] = '\0';
    char* encryptedName = (char*)alloca(33*sizeof(char));
    encryptedName[32] = '\0';
    char* keyStringKey = (char*)alloca(69*sizeof(char));
    keyStringKey[32] = '\0';
    char* keyString = (char*)alloca(33*sizeof(char));
    keyString[32] = '\0';
    char* encryptedKeyString = (char*)alloca(33*sizeof(char));
    encryptedKeyString[32] = '\0';
    char* key = (char*)alloca(17*sizeof(char));
    key[16] = '\0';

    MD5_CTX keyStringMD5;
    MD5_CTX keyMD5;

    for (int i = 0; i < numPacks; i++) {
        MD5_Init(&keyStringMD5);
        MD5_Init(&keyMD5);
        fseek(encryptionKeyFile,sizeof(uint8_t),SEEK_CUR);
        uint8_t nameLength = 0;
        fread(&nameLength,sizeof(uint8_t),1,encryptionKeyFile);
        fread(encryptedName,sizeof(char),nameLength,encryptionKeyFile);

        for (int i = 0; i < nameLength; i++)
            name[i] = encryptedName[i] ^ nameKey[i % 16];

        sprintf(keyStringKey,"%s%uB97C1205648A66E04F86A1B5D5AF9862", name,salt);
        MD5_Update(&keyStringMD5,keyStringKey,69);
        MD5_Final((unsigned char *)keyStringKey,&keyStringMD5);
        for (int i = 0; i < 0x20; i++)
            keyString[i] = encryptedKeyString[i] ^ keyStringKey[i % 16];

        MD5_Update(&keyMD5,keyString,32);
        MD5_Final((unsigned char*)key, &keyStringMD5);
        packs[std::string(name)] = std::string(key);
    }

}
