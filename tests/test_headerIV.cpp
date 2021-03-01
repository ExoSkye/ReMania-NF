#include <assetLayer.h>

int main(int argc, char** argv) {
    std::ifstream pack(std::string(argv[1])+"/assets/Packs/Game.pak");
    std::string ivStr = assetLayer::getHeaderIV(pack);
    uint64_t iv = (uint64_t)&ivStr[0];
    if (iv != 140737488348032ull) {
        printf("Test failed");
    }
    else {
        printf("Test passed");
    }
}