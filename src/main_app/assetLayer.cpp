//
// Created by Bob on 08/02/2021.
// 

#include "assetLayer.h"
#include "mbedtls/blowfish.h"

void assetLayer::printIndex(const char *file) {
    std::ifstream pakFile(file);
    std::ifstream encryptionKeyFile("assets/Packs/packlist.dat");

    std::string magic = getMagic(pakFile);
    logger::log(logger::INFO, ("The magic in the file is: "+magic).c_str(), "Assets");

    if (magic=="NadeoPak") {
        logger::log(logger::INFO, "Magic is correct","Assets");
    }
    else {
        logger::log(logger::FATAL, "File magic is incorrect, please check if the file is not corrupted", "Assets");
    }

    uint8_t encryptionVer = getPackListVer(pakFile);
    logger::log(logger::INFO, ("The encryption key file version is: "+std::to_string(encryptionVer)).c_str(),"Assets");

    // Adapted code from https://wiki.xaseco.org/wiki/Packlist.dat

    uint8_t numPacks = getNumPaks(pakFile);

    uint32_t salt = getSalt(pakFile);

    std::unordered_map<std::string,std::string> packs;

    for (int i = i; i < numPacks+1; i++) {
        std::string name = getName(i,salt,pakFile);
        std::string key = getKey(i,salt,name.c_str(),pakFile);
        packs[std::string(name)] = std::string(key);
    }
    logger::log(logger::INFO,"Finished processing packlist.dat","Assets");
    for (auto pair : packs) {
            logger::log(logger::VERBOSE,(pair.first+"\t:\t"+pair.second).c_str(),"Assets");
    }
}

uint32_t assetLayer::getSalt(std::ifstream &file) {
    file.seekg(6);
    readFileWithDecl(file, 6, 4, ret, uint32_t)
    return ret;
}

uint8_t assetLayer::getPackListVer(std::ifstream &file) {
    file.seekg(0);
    readFileWithDecl(file, 0, 1, ret, uint8_t)
    return ret;
}

uint8_t assetLayer::getNumPaks(std::ifstream &file) {
    readFileWithDecl(file, 1, 1, ret, uint8_t)
    return ret;
}

std::string assetLayer::getName(uint8_t index, uint32_t salt, std::ifstream &file) {
    long counter = getIndexStart(index,file);

    file.seekg(counter);
    uint8_t nameLength = 0;
    file.read((char*)&nameLength,1);

    file.seekg(counter+1);
    char encryptedName[32];
    file.read(encryptedName,nameLength);
    encryptedName[nameLength] = '\0';

    std::string name;
    std::string nameKeyString = "6611992868945B0B59536FC3226F3FD0"+std::to_string(salt);
    uint8_t nameKey[16];
    mbedtls_md5((unsigned char *) nameKeyString.c_str(), nameKeyString.size(),
                (unsigned char *) nameKey);

    for (int j = 0; j < nameLength; j++)
        name += (char)(encryptedName[j] ^ nameKey[j % 16]);

    return name;
}

std::string assetLayer::getKey(uint8_t index, uint32_t salt, const char *name, std::ifstream &file) {
    int start = getIndexStart(index,file);
    uint8_t nameLength = 0;
    file.seekg(start);
    file.read((char*)&nameLength,1);
    file.seekg(start+nameLength);
    uint8_t encryptedKeyString[32];
    file.read((char*)&encryptedKeyString,32);
    std::string KeyStringInput = name+std::to_string(salt)+"B97C1205648A66E04F86A1B5D5AF9862";
    uint8_t keyString[32];
    mbedtls_md5((unsigned char *) KeyStringInput.c_str(), KeyStringInput.size(),
                (unsigned char *) keyString);

    for (int j = 0; j < 0x20; j++) {
        keyString[j] = encryptedKeyString[j] ^ keyString[j % 16];
    }

    std::string key;
    key.resize(16,'\0');
    mbedtls_md5((unsigned char *) (std::string((char*)keyString)+"NadeoPak").c_str(), 40,
                (unsigned char *) key.data());

    return key;
}

long assetLayer::getIndexStart(uint8_t index, std::ifstream& file) {
    int counter = 11;
    uint8_t nameLength = 0;
    file.seekg(counter);
    file.read((char*)&nameLength,sizeof(uint8_t));
    for (int i = 0; i < index-1; i++) {
        file.seekg(counter);
        file.read((char*)&nameLength,sizeof(uint8_t));
        counter += nameLength + 34;
    }
    return counter;
}

std::string assetLayer::getMagic(std::ifstream &file) {
    std::string magic;
    magic.resize(8,'\0');
    file.read(magic.data(),8);
    return magic;
}

uint64_t assetLayer::CalcIVXor(uint64_t _ivXor, char *pInput, int count) {
    for (int i = 0; i < count; i++)
    {
        uint64_t lopart = _ivXor & 0xFFFFFFFF;
        uint64_t hipart = _ivXor >> 32;
        lopart = (pInput[i] | 0xAA) ^ ((lopart << 13) | (hipart >> 19));
        hipart = (_ivXor << 13) >> 32;
        _ivXor = (hipart << 32) | lopart;
    }
    return _ivXor;
}

std::string assetLayer::getHeaderIV(std::ifstream& file) {
    file.seekg(12);
    //printf("%llu\n", file.tellg());
    std::string iv;
    file.read((char*)&iv[0],8);
    //printf("%llu\n", file.tellg());
    return iv;
}

std::string assetLayer::decryptBlowfish(std::string& data, char* key, char* IV) {
    mbedtls_blowfish_context ctx;
    mbedtls_blowfish_init(&ctx);
    if (mbedtls_blowfish_setkey(&ctx,(const unsigned char*)key,128) != 0) {
        logger::log(logger::FATAL,"Setting key failed","Assets",__FILE__,__LINE__);
    }

    if (data.size()%8 != 0) {
        logger::log(logger::FATAL,"Data read from pack file didn't have a length which is a multiple of 8","Assets",__FILE__,__LINE__);
    }

    std::string out = data;
    //for (int j = 0; j < data.size(); j += 256) {
        if(mbedtls_blowfish_crypt_cbc(&ctx,MBEDTLS_BLOWFISH_DECRYPT,data.size(),(unsigned char*)IV,(unsigned char*)data.data(),(unsigned char*)out.data()) != 0) {
            logger::log(logger::ERROR,"Decryption failed","Assets",__FILE__,__LINE__);
        }
    //}
    mbedtls_blowfish_free(&ctx);
    return out;
}

uint32_t assetLayer::getPackVer(std::ifstream& file) {
    file.seekg(sizeof(char)*8);
    uint32_t version;
    file.read((char*)&version,4);
    if (version != 3) {
        logger::log(logger::FATAL,"Pack versions over than 3 (TMNF) are not supported. Make sure that these pack files are from TrackMania Nations Forever","Assets",__FILE__,__LINE__);
        return -1; // Unreachable code but the compiler doesn't want to compile it without
    }
    else {
        return version;
    }
}

void assetLayer::extractPaks() {
    ProtoFS::FilesystemX packs("assets/Packs");
    std::ifstream packlist("assets/Packs/packlist.dat");
    if (getPackListVer(packlist) != 1) {
        logger::log(logger::FATAL, "Pack list version != 1 (likely a corrupt file), Aborting...","Assets",__FILE__,__LINE__);
    }
    uint32_t salt = getSalt(packlist);

    std::unordered_map<std::string,std::string> keys;

    for (int i = 0; i < getNumPaks(packlist); i++) {
        keys[getName(i,salt,packlist)] = getKey(i, salt, getName(i,salt,packlist).c_str(), packlist);
    }
    for (auto i : packs.ls()) {
        if (i.getExt() != ".pak") {
            continue;
        }
        std::ifstream pack(i.filePath);
        if (getMagic(pack) != "NadeoPak") {
            logger::log(logger::FATAL, "Pak file magic != NadeoPak, Aborting","Assets",__FILE__,__LINE__);
        }
        std::string file_no_ext = i.fileName.substr(0,i.fileName.length()-4);
        std::string key = keys[file_no_ext];
        getPackVer(pack);
        std::string encrypted;
        pack.seekg(0,std::ios_base::seekdir::_S_end);
        int len = pack.tellg();
        encrypted.resize(len-24);
        pack.seekg(20);
        pack.read(encrypted.data(),encrypted.size());
        std::string iv = getHeaderIV(pack);
        std::string data = decryptBlowfish(encrypted,key.data(),iv.data());
        std::istringstream sstream(data);
        std::string md5;
        md5.resize(16);
        sstream.read(md5.data(),16);
        for (int pos = 0; pos < 16; pos++) {
            data[pos] = '\0';
        }
        mbedtls_md5_context ctx;
        mbedtls_md5_init(&ctx);
        std::string md5_ret;
        md5_ret.resize(16);
        mbedtls_md5_ret((const unsigned char *)data.c_str(), data.size(),
                        (unsigned char *)md5_ret.data());
        if (md5_ret != md5) {
            logger::log(logger::WARN,"Calculated MD5 sum of Pak file doesn't match the stored one","Assets",__FILE__,__LINE__);
        }
        sstream.seekg(52);
        uint32_t numFolders;
        sstream.read((char*)&numFolders,4);
        std::vector<std::pair<int,std::string>> folderIndicies;
        for (int j = 0; j < numFolders; j++) {
            uint32_t parentIndex;
            sstream.read((char*)&parentIndex, 4);
            std::string name;
            std::getline(sstream,name,'\0');
            folderIndicies.emplace_back(parentIndex, name);
            std::string path = name;
            auto lastPair = folderIndicies[parentIndex];
            while (lastPair.first != -1) {
                path.insert(0,lastPair.second+"/");
                lastPair = folderIndicies[lastPair.first];
            }
            printf("%s",path.c_str());
        }
    }
}
