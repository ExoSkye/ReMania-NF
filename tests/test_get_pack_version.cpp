#include <assetLayer.h>

int main(int argc, char** argv) {
    assetLayer layer;
    std::ifstream file(std::string(argv[1])+"/assets/Packs/Game.pak");
    if (layer.getPackVer(file) == 3) {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
}