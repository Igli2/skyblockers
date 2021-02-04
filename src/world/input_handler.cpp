#include <iostream>
#include <memory>
#include <cmath>

#include "input_handler.hpp"
#include "world.hpp"
#include "../gui/inventory.hpp"
#include "../resource/blocks.hpp"

InputHandler::InputHandler(MouseHandler* mouseHandler, KeyboardHandler* keyboardHandler, GUIHandler* guiHandler, World* world):
    scrollX{300},
    scrollY{300},
    guiHandler{guiHandler},
    world{world},
    pressed{false} {
        keyboardHandler->addKeyboardListener(this);
        mouseHandler->addMouseListener(this);
}

bool InputHandler::onKeyPressed(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::W:
            this->pressed[0] = true;
            return true;
        case sf::Keyboard::Key::S:
            this->pressed[1] = true;
            return true;
        case sf::Keyboard::Key::A:
            this->pressed[2] = true;
            return true;
        case sf::Keyboard::Key::D:
            this->pressed[3] = true;
            return true;
        case sf::Keyboard::Key::R:
            this->guiHandler->getInventory().setVisible(true);
            return true;
    }
    return false;
}

bool InputHandler::onKeyReleased(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::W:
            this->pressed[0] = false;
            return true;
        case sf::Keyboard::Key::S:
            this->pressed[1] = false;
            return true;
        case sf::Keyboard::Key::A:
            this->pressed[2] = false;
            return true;
        case sf::Keyboard::Key::D:
            this->pressed[3] = false;
            return true;
    }
    return false;
}

void InputHandler::updateScroll() {
    if (this->pressed[0]) {
        this->scrollY += this->scrollSpeed;
    }
    if (this->pressed[1]) {
        this->scrollY -= this->scrollSpeed;
    }
    if (this->pressed[2]) {
        this->scrollX += this->scrollSpeed;
    }
    if (this->pressed[3]) {
        this->scrollX -= this->scrollSpeed;
    }
}

bool InputHandler::onLeftClick(const sf::Vector2i& mousePos) {
    if (this->guiHandler->getInventory().getSelectedItem() != Blocks::AIR) {
        int blockX = std::floor(((float)mousePos.x - (float)this->scrollX) / 32);
        int blockY = std::floor(((float)mousePos.y - (float)this->scrollY) / 32);
        this->world->setBlock(blockX, blockY, this->guiHandler->getInventory().getSelectedItem());
        this->guiHandler->getInventory().removeItem(this->guiHandler->getInventory().getSelectedItem(), 1);
        return true;
    }
    return false;
}