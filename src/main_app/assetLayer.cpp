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

    std::string nameKeyString;
    nameKeyString = "6611992868945B0B59536FC3226F3FD0"+std::to_string(salt);

    uint8_t nameKey[16];
    mbedtls_md5((unsigned char *) nameKeyString.c_str(), 32*sizeof(char)+sizeof(uint32_t),
                (unsigned char *) nameKey);

    std::unordered_map<std::string,std::string> packs;

    std::string name;
    char encryptedName[32];
    std::string keyStringKey;
    char keyString[32];
    char encryptedKeyString[32];
    char key[16];
    for (int i = 0; i < numPacks; i++) {
        fseek(encryptionKeyFile,sizeof(uint8_t),SEEK_CUR);
        uint8_t nameLength = 0;
        fread(&nameLength,sizeof(uint8_t),1,encryptionKeyFile);
        fread(encryptedName,sizeof(char),nameLength,encryptionKeyFile);

        for (int j = 0; j < nameLength; i++)
            name[j] = encryptedName[j] ^ nameKey[j % 16];

        keyStringKey = name+std::to_string(salt)+"B97C1205648A66E04F86A1B5D5AF9862";
        MD5_Update(&keyStringMD5,keyStringKey,69);
        MD5_Final((unsigned char *)keyStringKey,&keyStringMD5);
        mbedtls_md5((unsigned char *) keyStringKey.c_str(), keyStringKey.size(),
                    (unsigned char *) keyString);
        for (int j = 0; j < 0x20; i++)
            keyString[j] = encryptedKeyString[j] ^ keyStringKey[j % 16];

        MD5_Update(&keyMD5,keyString,32);
        MD5_Final((unsigned char*)key, &keyStringMD5);
        packs[std::string(name)] = std::string(key);
    }

}
