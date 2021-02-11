//
// Created by protobit on 10/02/2021.
//

#include <assetLayer.h>

int main(int argc, char** argv) {
    assetLayer layer;
    std::ifstream file(std::string(argv[1])+"/assets/Packs/packlist.dat");
    std::ofstream log("log.log");
    bool passed = true;
    uint32_t salt = layer.getSalt(file);
    std::vector<std::string> names = {"0",
                                      "1",
                                      "2",
                                      "3",
                                      "4",
                                      "5",
                                      "6",
                                      "7",
                                      "8",
                                      "9"};
    
    for (int i = 0; i < 10; i++) {
        log << layer.getName(i+1,salt,file) << "\n";
        if (layer.getName(i+1,salt,file) != names[i]) {
            passed = false;
        }
    }   
    
    if (passed) {
        printf("Test passed");
    }
    else {
        printf("Test failed");
    }
    log.close();
}