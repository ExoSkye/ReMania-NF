#include <assetLayer.h>

int main(int argc, char** argv) {
    std::ifstream pack(std::string(argv[1])+"/assets/Packs/Game.pak");
    printf("%lu\n",assetLayer::getHeaderIV(pack));
    if (assetLayer::getHeaderIV(pack) != 10940076322615098153ull) {
        printf("Test failed");
    }
    else {
        printf("Test passed");
    }
}