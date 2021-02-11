//
// Created by protobit on 10/02/2021.
//

#include <assetLayer.h>

int main() {
    assetLayer layer;
    std::ifstream file("assets/Packs/packlist.dat");
    bool passed = true;
    uint32_t salt = layer.getSalt(file);
    std::vector<int> start_pos_vec = {0xB, 0x35, 0x5B, 0x83, 0xAA, 0xD1, 0xF9, 0x120, 0x145, 0x16E};

    for (int i = 0; i < 10; i++) {
        if (layer.getIndexStart(i,file) != start_pos_vec[i]) {
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