#include <assetLayer.h>

struct testData {
    uint64_t start_ivXor;
    std::string pInput;
    uint64_t expected_ivXor;
};

#include "ivXor_data.inl"

int main() {
    bool passed = true;
    for (auto i : tests) {
        uint64_t start = i.start_ivXor;
        std::string& text = i.pInput;
        if (assetLayer::CalcIVXor(start,text.data(),text.size()) != i.expected_ivXor) {
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