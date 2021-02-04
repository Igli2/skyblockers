#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "blocks.hpp"
#include "../util/util.hpp"

class ResourceManager {
    private:
        std::unique_ptr<Texture> blockTextures[Blocks::MAX];
        std::unique_ptr<BaseBlock> blockSingletons[Blocks::MAX];
        uint time;
        sf::Font font;

        std::unique_ptr<Texture> loadBlockTexture(std::string filename);

    public:
        ResourceManager();
        void renderTexture(float x, float y, Blocks id, sf::RenderWindow& window);
        void tick();
        const sf::Font& getFont();
};