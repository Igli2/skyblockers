#include <iostream>

#include "resource_manager.hpp"

ResourceManager::ResourceManager() {
    this->font.loadFromFile("../res/fonts/OpenSansExtraBold.ttf");

    this->blockTextures[Blocks::AIR] = loadBlockTexture("air.png", "air_bottom.png");
    this->blockTextures[Blocks::GRASS_SEEDS] = loadBlockTexture("grass_seeds.png", "grass_seeds_bottom.png");

    this->blockSingletons[Blocks::AIR] = std::make_unique<BaseBlock>("air.json");
    this->blockSingletons[Blocks::GRASS_SEEDS] = std::make_unique<GrowableBlock>("grass_seeds.json");
}

std::unique_ptr<Texture> ResourceManager::loadBlockTexture(std::string filename, std::string bottomFilename) {
    std::unique_ptr<Texture> t = std::make_unique<Texture>();

    sf::Image image;
    image.loadFromFile("../res/textures/blocks/" + filename);
    for (int i = 0; i < (image.getSize().y / 32); ++i) {
        sf::Texture subTexture;
        subTexture.loadFromImage(image, sf::IntRect{0, 0 + 32 * i, 32, 32});
        t->texture.push_back(std::move(subTexture));
    }

    sf::Image darkerImage;
    darkerImage.loadFromFile("../res/textures/blocks/" + bottomFilename);
    for (int i = 0; i < (darkerImage.getSize().y / 8); ++i) {
        sf::Texture subTexture;
        subTexture.loadFromImage(darkerImage, sf::IntRect{0, 0 + 8 * i, 32, 8});
        t->bottomTexture.push_back(std::move(subTexture));
    }

    t->rect.setTexture(&t->texture[0]);
    t->rect.setSize(sf::Vector2f{32, 32});
    t->bottomRect.setTexture(&t->bottomTexture[0]);
    t->bottomRect.setSize(sf::Vector2f{32, 8});
    return std::move(t);
}

void ResourceManager::renderTexture(float x, float y, BlockData data, sf::RenderWindow& window, bool drawBottom) {
    Blocks id = data.blockType;
    if (id != Blocks::AIR) {
        if (this->blockSingletons[id]->useBlockStage) {
            this->blockTextures[id]->rect.setTexture(&this->blockTextures[id]->texture[data.stage]);
            this->blockTextures[id]->bottomRect.setTexture(&this->blockTextures[id]->bottomTexture[data.stage]);
        }

        this->blockTextures[id]->rect.setPosition(x, y);
        window.draw(this->blockTextures[id]->rect);

        if (drawBottom) {
            this->blockTextures[id]->bottomRect.setPosition(x, y + 32);
            window.draw(this->blockTextures[id]->bottomRect);
        }
    }
}

void ResourceManager::tick() {
    this->time += 1;
    this->updateTextures();
}

void ResourceManager::updateTextures() {
    int id = 0;
    for (std::unique_ptr<Texture>& t : this->blockTextures) {
        if (this->blockSingletons[id]->isAnimated) {
            int frames = t->texture.size();
            int textureIndex = (this->time / this->blockSingletons[id]->animationTime) % frames;
            t->rect.setTexture(&t->texture[textureIndex]);
            t->bottomRect.setTexture(&t->bottomTexture[textureIndex]);
        }
        id += 1;
    }
}

const sf::Font& ResourceManager::getFont() {
    return this->font;
}

std::unique_ptr<BaseBlock>& ResourceManager::getBlockClass(Blocks id) {
    return this->blockSingletons[id];
}