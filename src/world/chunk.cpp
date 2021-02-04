#include <fstream>

#include "chunk.hpp"

Chunk::Chunk(int chunkX, int chunkY): chunkX{chunkX}, chunkY{chunkY} {
    for (int i = 0; i < 1024; i++) {
        this->blocks[i] = BlockData{Blocks::AIR};
    }
}

void Chunk::save() {
    std::string filename = "../saves/" + std::to_string(this->chunkX) + "." + std::to_string(this->chunkY) + ".chunk";
    std::ofstream file(filename);

    for (BlockData& bd : this->blocks) {
        file.write((char*)&bd.blockType, sizeof(bd.blockType));
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

void Chunk::render(sf::RenderWindow& window, ResourceManager& resourceManager, const int& scrollX, const int& scrollY) {
    for (int i = 0; i < 1024; i++) {
        int x = (i % 32) * 32 + this->chunkX * 2048 + scrollX;
        int y = (i / 32) * 32 + this->chunkY * 2048 + scrollY;
        resourceManager.renderTexture(x, y, this->blocks[i].blockType, window);
    }
}