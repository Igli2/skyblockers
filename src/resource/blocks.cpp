#include <iostream>
#include <simdjson.h>

#include "blocks.hpp"
#include "../world/world.hpp"
#include "../util/util.hpp"

BaseBlock::BaseBlock(std::string filename): e{this->rd()}, chance{0, 100} {
    this->loadBlockData(filename);
}

void BaseBlock::tick(World& world, BlockData& blockData, int x, int y) {
    if (this->isMutable) {
        if (world.getBlock(x + 1, y).blockType == blockData.blockType &&
            world.getBlock(x - 1, y).blockType == blockData.blockType &&
            world.getBlock(x, y + 1).blockType == blockData.blockType &&
            world.getBlock(x, y - 1).blockType == blockData.blockType) {
                if (this->chance(this->e) < this->mutationChance) {
                    world.setBlock(x, y, this->mutatedBlock);
                }
            }
    }
}

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
        this->blockDrops[getBlockType(key)] = (double)entry.value;
    }

    this->isMutable = element["isMutable"];
    this->mutationChance = (double)element["mutationChance"];
    std::string_view rawType = element["mutatedBlock"];
    this->mutatedBlock = getBlockType(rawType.data());
}

std::map<Blocks, int> BaseBlock::getDrops(const BlockData& bd) {
    std::map<Blocks, int> output;
    if ((this->useBlockStage && bd.stage == this->maxStages) || (!this->useBlockStage)) {
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
    } else {
        output[bd.blockType] = 1;
    }

    return output;
}



GrowableBlock::GrowableBlock(std::string filename): BaseBlock{filename} {}

void GrowableBlock::tick(World& world, BlockData& blockData, int x, int y) {
    BaseBlock::tick(world, blockData, x, y);
    if (this->chance(this->e) < this->growthChance && this->maxStages > blockData.stage) {
        blockData.stage += 1;
    }
}



CollectorBlock::CollectorBlock(std::string filename): BaseBlock{filename} {}