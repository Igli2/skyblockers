#pragma once

#include "../util/util.hpp"
#include "../resource/resource_manager.hpp"

class Chunk {
    private:
        BlockData blocks[1024];
        int chunkX;
        int chunkY;
        //pos: upper left of chunk in chunks, size: 2048px, 32x32 blocks

    public:
        Chunk(int chunkX, int chunkY);
        void save();
        void load(std::string path);
        const int& getX();
        const int& getY();
        void setBlock(int blockPosX, int blockPosY, Blocks blockId);
        void render(sf::RenderWindow& window, ResourceManager& resourceManager, const int& scrollX, const int& scrollY);
        void tick(World& world, ResourceManager& resourceManager);
};