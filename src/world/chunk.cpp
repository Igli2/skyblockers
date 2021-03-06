#include <fstream>
#include <iostream>

#include "chunk.hpp"

Chunk::Chunk(int chunkX, int chunkY): chunkX{chunkX}, chunkY{chunkY} {
    for (int i = 0; i < 1024; i++) {
        this->blocks[i] = BlockData{Blocks::AIR};
    }
}

void Chunk::save() {
    std::string filename = "../saves/world/" + std::to_string(this->chunkX) + "." + std::to_string(this->chunkY) + ".chunk";
    std::ofstream file(filename);

    for (BlockData& bd : this->blocks) {
        file.write((char*)&bd, sizeof(bd));
    }
}

void Chunk::load(std::string path) {
    std::ifstream file(path);
    for (int i = 0; i < 1024; i++) {
        file.read((char*)&this->blocks[i], sizeof(this->blocks[i]));
    }
}

const int& Chunk::getX() {
    return this->chunkX;
}

const int& Chunk::getY() {
    return this->chunkY;
}

void Chunk::setBlock(int blockPosX, int blockPosY, Blocks blockId) {
    int index = blockPosY * 32 + blockPosX;
    this->blocks[index] = BlockData{blockId};
}

const BlockData& Chunk::getBlock(int x, int y) {
    int index = y * 32 + x;
    return this->blocks[index];
}

void Chunk::render(sf::RenderWindow& window, ResourceManager& resourceManager, const int& scrollX, const int& scrollY) {
    for (int i = 0; i < 1024; ++i) {
        int x = (i % 32) * 32 + this->chunkX * 1024 + scrollX;
        int y = (i / 32) * 32 + this->chunkY * 1024 + scrollY;
        resourceManager.renderTexture(x, y, this->blocks[i], window);
    }
}

void Chunk::tick(World& world, ResourceManager& resourceManager) {
    for (int i = 0; i < 1024; ++i) {
        BlockData& bd = this->blocks[i];
        resourceManager.getBlockClass(bd.blockType)->tick(world, bd, this->chunkX * 32 + i % 32, this->chunkY * 32 + i / 32);
    }
}