#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../resource/blocks.hpp"

struct Texture {
    std::vector<sf::Texture> texture;
    std::vector<sf::Texture> bottomTexture;
    sf::RectangleShape rect;
    sf::RectangleShape bottomRect;

    Texture() = default;
    Texture(const Texture& other) = delete;
    Texture(Texture&& other) = default;
    Texture& operator=(const Texture& other) = delete;
    Texture& operator=(Texture&& other) = default;
};

struct BlockData {
    Blocks blockType;
    uint stage;
};

bool endsWith(const std::string& str, const std::string& suffix);
std::string filenameFromPath(const std::string& str);
Blocks getBlockType(std::string str);