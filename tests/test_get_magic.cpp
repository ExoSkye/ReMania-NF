//
// Created by protobit on 10/02/2021.
//

#include <assetLayer.h>

int main() {
    assetLayer layer;
    std::ifstream file("assets/Packs/Game.pak");
    if (layer.getMagic(file) == "NadeoPak") {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
}