#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    // Code for getting values used in the key test
    logger::verbose = true;
    std::ifstream file("assets/Packs/packlist.dat");
    uint32_t salt = assetLayer::getSalt(file);
    for (int i = 1; i < 11; i++) {
        std::string key = assetLayer::getKey(i,salt,assetLayer::getName(i,salt,file).c_str(),file);
        printf("%s\n",key.c_str());
    }
    //assetLayer::printIndex("assets/Packs/Game.pak");
    return 0;
}
