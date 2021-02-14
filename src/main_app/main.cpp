#include "mbedtls/blowfish.h"
#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    // Code for getting values used in the key test
    logger::verbose = true;
    for (int i = 0; i < 4; i++) {
        mbedtls_blowfish_context ctx;
        mbedtls_blowfish_init(&ctx);
        std::mt19937_64 rand((std::random_device()()));
        std::string IV;
        std::string key;
        std::string data;
        for (int i = 0; i < 8; i++) {
            IV += (char)0x41+rand()%(0x5A-0x41);
        }
        for (int i = 0; i < 16; i++) {
            key += (char)0x41+rand()%(0x5A-0x41);
        }
        for (int i = 0; i < 1024; i++) {
            data += (char)0x41+rand()%(0x5A-0x41);
        }
        std::ofstream file(std::string("../../tests/data/"+std::to_string(i)+".bin"));
        mbedtls_blowfish_setkey(&ctx, (unsigned char*)key.c_str(), 256);
        std::string out;
        out.resize(1024);
        printf("fileData {\n"
        "    \x22%s\x22,\n"
        "    \x22\\x%02hhx\\x%02hhx\\x%02hhx\\x%02hhx\\x%02hhx\\x%02hhx\\x%02hhx\\x%02hhx\x22,\n"
        "    \x22%s\x22,\n"
        "    \x22%s\x22\n"
        "},\n",key.c_str(),IV[0],IV[1],IV[2],IV[3],IV[4],IV[5],IV[6],IV[7],std::string("data/"+std::to_string(i)+".bin").c_str(),data.c_str());
        mbedtls_blowfish_crypt_cbc(&ctx, MBEDTLS_BLOWFISH_ENCRYPT, 1024, (unsigned char *)IV.data(), (unsigned char*)data.data(), (unsigned char *)out.data());
        out.shrink_to_fit();
        file.write(out.data(),out.size());
        file.close();
        mbedtls_blowfish_free(&ctx);
    }
    //assetLayer::printIndex("assets/Packs/Game.pak");
    return 0;
}
