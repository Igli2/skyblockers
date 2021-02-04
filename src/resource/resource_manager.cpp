#include <iostream>

#include "resource_manager.hpp"

ResourceManager::ResourceManager() {
    this->font.loadFromFile("../res/fonts/OpenSansExtraBold.ttf");

    this->blockTextures[Blocks::AIR] = loadBlockTexture("air.png");
    this->blockTextures[Blocks::DIRT] = loadBlockTexture("dirt.png");
    this->blockTextures[Blocks::GABBRO] = loadBlockTexture("gabbro.png");
    this->blockTextures[Blocks::MONZONITE] = loadBlockTexture("monzonite.png");
    this->blockTextures[Blocks::PHYLLITE] = loadBlockTexture("phyllite.png");
    this->blockTextures[Blocks::FLINT] = loadBlockTexture("flint.png");
    this->blockTextures[Blocks::GRASS_SEEDS] = loadBlockTexture("grass_seeds.png");
    this->blockTextures[Blocks::BIOMASS] = loadBlockTexture("biomass.png");
    this->blockTextures[Blocks::DAISY] = loadBlockTexture("daisy.png");
    this->blockTextures[Blocks::COLLECTOR] = loadBlockTexture("collector.png");

    this->blockSingletons[Blocks::DIRT] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::GABBRO] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::MONZONITE] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::PHYLLITE] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::FLINT] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::GRASS_SEEDS] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::BIOMASS] = std::make_unique<BaseBlock>();
    this->blockSingletons[Blocks::DAISY] = std::make_unique<FlowerBlock>();
    this->blockSingletons[Blocks::COLLECTOR] = std::make_unique<BaseBlock>();
}

std::unique_ptr<Texture> ResourceManager::loadBlockTexture(std::string filename) {
    std::unique_ptr<Texture> t = std::make_unique<Texture>();

    sf::Image image;
    image.loadFromFile("../res/textures/blocks/" + filename);
    for (int i = 0; i < (image.getSize().y / 32); ++i) {
        sf::Texture subTexture;
        subTexture.loadFromImage(image, sf::IntRect{0, 0 + 32 * i, 32, 32});
        t->texture.push_back(std::move(subTexture));
    }

    t->rect.setTexture(&t->texture[0]);
    t->rect.setSize(sf::Vector2f{32, 32});
    return std::move(t);
}

void ResourceManager::renderTexture(float x, float y, Blocks id, sf::RenderWindow& window) {
    if (id != Blocks::AIR) {
        this->blockTextures[id]->rect.setPosition(x, y);
        window.draw(this->blockTextures[id]->rect);
    }
}

void ResourceManager::tick() {
    this->time += 1;
    int id = 0;
    for (std::unique_ptr<Texture>& t : this->blockTextures) {
        if (t->isAnimated()) {
            int frames = t->texture.size();
            int textureIndex = (this->time / this->blockSingletons[id]->animationTime) % frames;
            t->rect.setTexture(&t->texture[textureIndex]);
        }
        id += 1;
    }
}

const sf::Font& ResourceManager::getFont() {
    return this->font;
}