#include <assetLayer.h>

int main(int argc, char** argv) {
    std::ifstream file(std::string(argv[1])+"/assets/Packs/Game.pak");
    if (assetLayer::getPackVer(file) == 3) {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
}