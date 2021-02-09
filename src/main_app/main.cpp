#include "utils.h"
#include "pch.h"
#include "assetLayer.h"

int main() {
    assetLayer layer;
    logger::verbose = true;
    layer.printIndex("assets/Packs/Game.pak");
    return 0;
}
