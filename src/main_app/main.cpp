#include "mbedtls/blowfish.h"
#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    // Code for getting values used in the key test
    logger::verbose = true;
    std::mt19937_64 randomGen;
    printf("std::vector<testData> {\n");
    for (int i = 0; i < 128; i++) {
        //printf("// Generate pInput\n");
        std::string pInput;
        uint64_t length = randomGen() % 1024;
        for (int j = 0; j < length; j++) {
            pInput += (char)0x41+randomGen()%(0x5A-0x41);
        }
        //printf("// Generate start\n");
        uint64_t start = randomGen();
        //printf("// Calculate ivXor\n");
        uint64_t expected_ivXor = assetLayer::CalcIVXor(start,pInput.data(),length);
        printf("\ttestData {\n"
    "\t\t%" PRIu64 ",\n"
    "\t\t\x22%s\x22,\n"
    "\t\t%" PRIu64 "\n"
        "\t},\n",start,pInput.c_str(),expected_ivXor);
    }
    printf("};");
    //assetLayer::printIndex("assets/Packs/Game.pak");
    return 0;
}
