#include <filesystem>
#include <string>
#include <charconv>
#include <cmath>
#include <iostream>

#include "world.hpp"

World::World(MouseHandler* mouseHandler, KeyboardHandler* keyboardHandler, GUIHandler* guiHandler): inputHandler{std::make_unique<InputHandler>(mouseHandler, keyboardHandler, guiHandler, this)} {
    if (std::filesystem::exists("../saves")) {
        if (std::filesystem::exists("../saves/world")) {
            this->loadChunkFiles();
        } else {
            std::filesystem::create_directory("../saves/world");
            this->setStartBlocks();
        }
    } else {
        std::filesystem::create_directory("../saves");
        std::filesystem::create_directory("../saves/world");
        this->setStartBlocks();
    }
}

void World::loadChunkFiles() {
    for (auto& file : std::filesystem::directory_iterator("../saves/world")) {
        std::string filename = filenameFromPath(file.path());
        int chunkX;
        int chunkY;
        std::from_chars(filename.data(), filename.data() + filename.find("."), chunkX);
        std::from_chars(filename.data() + filename.find(".") + 1, filename.data() + filename.length(), chunkY);

        Chunk c = Chunk{chunkX, chunkY};
        c.load(file.path());
        this->chunks.emplace_back(std::move(c));
    }
}

void World::saveAll() {
    for (Chunk& c : this->chunks) {
        c.save();
    }
}

void World::setBlock(int x, int y, Blocks blockId) {
    int chunkX = std::floor((float)x / 32);
    int chunkY = std::floor((float)y / 32);

    if (!this->doesChunkExist(chunkX, chunkY)) {
        this->chunks.push_back(Chunk{chunkX, chunkY});
    }

    for (Chunk& c : this->chunks) {
        if (chunkX == c.getX() && chunkY == c.getY()) {
            c.setBlock(this->toChunkPos(x), this->toChunkPos(y), blockId);
        }
    }
}

bool World::doesChunkExist(int x, int y) {
    for (Chunk& c : this->chunks) {
        if (x == c.getX() && y == c.getY()) {
            return true;
        }
    }
    return false;
}

int World::toChunkPos(int blockPos) {
    while (blockPos < 0) {
        blockPos += 32;
    }
    while (blockPos > 31) {
        blockPos -= 32;
    }
    return blockPos;
}

void World::renderChunks(sf::RenderWindow& window, ResourceManager& resourceManager) {
    for (Chunk& c : this->chunks) {
        c.render(window, resourceManager, this->inputHandler->scrollX, this->inputHandler->scrollY);
    }

    this->inputHandler->updateScroll();
}

void World::setStartBlocks() {
    this->setBlock(0, 0, Blocks::DIRT);
}

const std::unique_ptr<InputHandler>& World::getInputHandler() {
    return this->inputHandler;
}