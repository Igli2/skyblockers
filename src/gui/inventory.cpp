#include <iostream>

#include "inventory.hpp"

Inventory::Inventory(): itemCount{}, visible{false} {
    this->slot.setSize(sf::Vector2f{48, 48});
    this->slot.setFillColor(sf::Color{100, 100, 100, 75});
    this->slot.setOutlineThickness(2);
    this->slot.setOutlineColor(sf::Color{100, 100, 100});
    this->text.setCharacterSize(14);
    this->text.setFillColor(sf::Color::Black);
}

void Inventory::render(sf::RenderWindow& window, ResourceManager& resourceManager) {
    if (this->visible) {
        this->text.setFont(resourceManager.getFont());

        int c = 0;
        for (const auto& [key, value] : this->itemCount) {
            this->slot.setPosition(c * 64 + 56, 56);
            this->text.setString(std::to_string(value));
            this->text.setPosition(c * 64 + 102 - this->text.getLocalBounds().width, 88);

            window.draw(this->slot);
            resourceManager.renderTexture(c * 64 + 64, 64, key, window);
            window.draw(this->text);

            ++c;
        }
    }
}

void Inventory::addItem(Blocks id, uint amount) {
    this->itemCount[id] += amount;
}

bool Inventory::onLeftClick(const sf::Vector2i& mousePos) {
    int c = 0;
    for (const auto& [key, value] : this->itemCount) {
        if (mousePos.x > (c * 64 + 56) && mousePos.x < (c * 64 + 104)) {
            if (mousePos.y > (56) && mousePos.y < (104)) {
                std::cout << key << " " << value << std::endl;
                return true;
            }
        }
        ++c;
    }
    return false;
}

void Inventory::setVisible(bool state) {
    this->visible = state;
}

const bool& Inventory::isVisible() {
    return this->visible;
}