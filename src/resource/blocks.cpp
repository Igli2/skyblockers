#include <iostream>

#include "blocks.hpp"
#include "../world/world.hpp"
#include "../util/util.hpp"

BaseBlock::BaseBlock(): animationTime{60}, isAnimated{true} {}
void BaseBlock::tick(World& world, BlockData& blockData, int x, int y) {}


void FlowerBlock::tick(World& world, BlockData& blockData, int x, int y) {}