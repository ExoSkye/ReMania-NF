//
// Created by protobit on 10/02/2021.
//

#include <assetLayer.h>

int main(int argc, char** argv) {
    std::ifstream file(std::string(argv[1])+"/assets/Packs/Game.pak");
    if (assetLayer::getMagic(file) == "NadeoPak") {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
}