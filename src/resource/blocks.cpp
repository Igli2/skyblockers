#include <iostream>
#include <simdjson.h>

#include "blocks.hpp"
#include "../world/world.hpp"
#include "../util/util.hpp"

BaseBlock::BaseBlock(std::string filename): e{this->rd()}, chance{0, 100} {
    this->loadBlockData(filename);
}

void BaseBlock::tick(World& world, BlockData& blockData, int x, int y) {}

void BaseBlock::loadBlockData(std::string filename) {
    simdjson::dom::parser parser;
    simdjson::dom::element element = parser.load("../res/blockdata/" + filename);

    this->animationTime = (int64_t)element["animationTime"];
    this->isAnimated = element["isAnimated"];
    this->useBlockStage = element["useBlockStage"];
    this->maxStages = (uint64_t)element["maxStages"];
    this->growthChance = (double)element["growthChance"];

    simdjson::dom::object dropsList = element["drops"];
    for (auto& entry : dropsList) {
        std::string key(entry.key.data(), entry.key.size());
        if (key == "GRASS_SEEDS") {
            this->blockDrops[Blocks::GRASS_SEEDS] = (double)entry.value;
        }
    }
}

std::map<Blocks, int> BaseBlock::getDrops() {
    std::map<Blocks, int> output;
    for (auto [blockId, c] : this->blockDrops) {
        while (c >= 100) {
            if (output.contains(blockId)) {
                output[blockId] += 1;
            } else {
                output[blockId] = 1;
            }
            c -= 100;
        }

        if (this->chance(this->e) < c) {
            if (output.contains(blockId)) {
                output[blockId] += 1;
            } else {
                output[blockId] = 1;
            }
        }
    }
    return output;
}



GrowableBlock::GrowableBlock(std::string filename): BaseBlock{filename} {}

void GrowableBlock::tick(World& world, BlockData& blockData, int x, int y) {
    if (this->chance(this->e) < this->growthChance && this->maxStages > blockData.stage) {
        blockData.stage += 1;
    }
}



CollectorBlock::CollectorBlock(std::string filename): BaseBlock{filename} {}