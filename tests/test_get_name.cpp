//
// Created by protobit on 10/02/2021.
//

#include <assetLayer.h>

int main() {
    assetLayer layer;
    std::ifstream file("assets/Packs/packlist.dat");
    bool passed = true;
    uint32_t salt = layer.getSalt(file);
    std::vector<std::string> names = {"resource",
                                      "game",
                                      "alpine",
                                      "speed",
                                      "rally",
                                      "island",
                                      "coast",
                                      "bay",
                                      "stadium"};

    for (int i = 0; i < 10; i++) {
        if (layer.getName(i,salt,file) != names[i]) {
            passed = false;
        }
    }

    if (passed) {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
}