#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>

#include "inventory.hpp"

Inventory::Inventory(): itemCount{}, visible{false}, selectedItem{Blocks::AIR} {
    this->slot.setSize(sf::Vector2f{48, 48});
    this->slot.setFillColor(sf::Color{100, 100, 100, 75});
    this->slot.setOutlineThickness(2);
    this->slot.setOutlineColor(sf::Color{100, 100, 100});
    this->text.setCharacterSize(14);
    this->text.setFillColor(sf::Color::Black);

    if (std::filesystem::exists("../saves")) {
        if (!std::filesystem::exists("../saves/player")) {
            std::filesystem::create_directory("../saves/player");
        } else {
            this->load();
        }
    } else {
        std::filesystem::create_directory("../saves");
        std::filesystem::create_directory("../saves/player");
    }
}

void Inventory::render(sf::RenderWindow& window, ResourceManager& resourceManager, int scrollX, int scrollY) {
    if (this->visible) {
        this->text.setFont(resourceManager.getFont());

        int c = 0;
        for (const auto& [key, value] : this->itemCount) {
            this->slot.setPosition(c * 64 + 56, 56);
            this->text.setString(std::to_string(value));
            this->text.setPosition(c * 64 + 102 - this->text.getLocalBounds().width, 88);

            window.draw(this->slot);
            resourceManager.renderTexture(c * 64 + 64, 64, BlockData{key, 0}, window, false);
            window.draw(this->text);

            ++c;
        }
    }
    if (this->selectedItem != Blocks::AIR) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int blockX = std::floor(((float)mousePos.x - (float)scrollX) / 32);
        int blockY = std::floor(((float)mousePos.y - (float)scrollY) / 32);
        resourceManager.renderTexture(blockX * 32 + scrollX, blockY * 32 + scrollY, BlockData{this->selectedItem, 0}, window, false);
    }
}

void Inventory::addItem(Blocks id, uint amount) {
    this->itemCount[id] += amount;
}

bool Inventory::onLeftClick(const sf::Vector2i& mousePos) {
    if (this->visible) {
        int c = 0;
        for (const auto& [key, value] : this->itemCount) {
            if (mousePos.x > (c * 64 + 56) && mousePos.x < (c * 64 + 104)) {
                if (mousePos.y > (56) && mousePos.y < (104)) {
                    this->selectedItem = key;
                    return true;
                }
            }
            ++c;
        }
    }
    return false;
}

bool Inventory::onRightClick(const sf::Vector2i& mousePos) {
    if (this->selectedItem != Blocks::AIR) {
        this->selectedItem = Blocks::AIR;
        return true;
    }
    return false;
}

void Inventory::setVisible(bool state) {
    this->visible = state;
}

const bool& Inventory::isVisible() {
    return this->visible;
}

void Inventory::save() {
    std::ofstream file("../saves/player/inv");

    uint size = this->itemCount.size();
    file.write((char*)&size, sizeof(size));
    for (const auto& [key, value] : this->itemCount) {
        file.write((char*)&key, sizeof(key));
        file.write((char*)&value, sizeof(value));
    }
}

void Inventory::load() {
    std::ifstream file("../saves/player/inv");
    if (file.is_open()) {
        uint size;
        file.read((char*)&size, sizeof(size));

        for (uint i = 0; i < size; ++i) {
            Blocks key;
            uint value;
            file.read((char*)&key, sizeof(key));
            file.read((char*)&value, sizeof(value));
            this->itemCount[key] = value;
        }
    }
}

const Blocks& Inventory::getSelectedItem() {
    return this->selectedItem;
}

bool Inventory::removeItem(Blocks id, uint amount) {
    if (this->itemCount.contains(id)) {
        if (this->itemCount[id] > amount) {
            this->itemCount[id] -= amount;
            return true;
        } else if (this->itemCount[id] == amount) {
            this->itemCount.erase(id);
            return true;
        }
    }
    return false;
}