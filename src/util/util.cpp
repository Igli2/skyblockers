#include "util.hpp"

bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string filenameFromPath(const std::string& str) {
    bool isFilename = false;
    std::string out = "";

    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] == '/') {
            break;
        }
        if (isFilename) {
            out.insert(0, 1, str[i]);
        }
        if (str[i] == '.') {
            isFilename = true;
        }
    }
    return out;
}

Blocks getBlockType(std::string str) {
    if (str == "GRASS_SEEDS") {
        return Blocks::GRASS_SEEDS;
    } else if (str == "INVASIVE_GRASS_SEEDS") {
        return Blocks::INVASIVE_GRASS_SEEDS;
    }
    return Blocks::AIR;
}