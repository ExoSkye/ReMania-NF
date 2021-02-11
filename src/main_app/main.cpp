#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    // Code for getting values used in the key test
    assetLayer layer;
    logger::verbose = true;
    std::ifstream file("assets/Packs/packlist.dat");
    uint32_t salt = layer.getSalt(file);
    for (int i = 1; i < 11; i++) {
        std::string key = layer.getKey(i,salt,layer.getName(i,salt,file).c_str(),file);
        printf("%s\n",key.c_str());
    }
    //layer.printIndex("assets/Packs/Game.pak");
    return 0;
}
