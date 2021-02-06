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

        std::unique_ptr<Texture> loadBlockTexture(std::string filename, std::string bottomFilename);
        void updateTextures();

    public:
        ResourceManager();
        void renderTexture(float x, float y, BlockData data, sf::RenderWindow& window, bool drawBottom=true);
        void tick();
        const sf::Font& getFont();
        std::unique_ptr<BaseBlock>& getBlockClass(Blocks id);
};