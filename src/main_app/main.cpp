#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    assetLayer layer;
    logger::verbose = true;
    std::ifstream file("assets/Packs/packlist.dat");
    uint32_t salt = layer.getSalt(file);
    for (int i = 0; i < 10; i++) {
        std::string name = layer.getName(i,salt,file);
        printf("%s\n",name.c_str());
    }
    //layer.printIndex("assets/Packs/Game.pak");
    return 0;
}
