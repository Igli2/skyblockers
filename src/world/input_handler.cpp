#include <memory>

#include "input_handler.hpp"
#include "../gui/inventory.hpp"
#include "../resource/blocks.hpp"

InputHandler::InputHandler(KeyboardHandler* keyboardHandler, GUIHandler* guiHandler):
    scrollX{300},
    scrollY{300},
    guiHandler{guiHandler},
    pressed{false} {
        keyboardHandler->addKeyboardListener(this);
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
            this->guiHandler->openInventory();
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