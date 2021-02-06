#include <iostream>
#include <simdjson.h>

#include "blocks.hpp"
#include "../world/world.hpp"
#include "../util/util.hpp"

BaseBlock::BaseBlock(std::string filename): animationTime{60}, isAnimated{true} {
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
}



GrowableBlock::GrowableBlock(std::string filename): BaseBlock{filename}, e{this->rd()}, chance{0, 100} {}

void GrowableBlock::tick(World& world, BlockData& blockData, int x, int y) {
    if (this->chance(this->e) < this->growthChance && this->maxStages > blockData.stage) {
        blockData.stage += 1;
    }
}



CollectorBlock::CollectorBlock(std::string filename): BaseBlock{filename} {}