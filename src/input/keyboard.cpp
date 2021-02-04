#include <algorithm>

#include "keyboard.hpp"

AbstractKeyboardListener::AbstractKeyboardListener(): isActive{true} {}

void AbstractKeyboardListener::setActive(bool state) {
    this->isActive = state;
}

const bool& AbstractKeyboardListener::getActive() {
    return this->isActive;
}

bool AbstractKeyboardListener::onKeyPressed(sf::Keyboard::Key key) {return false;}
bool AbstractKeyboardListener::onKeyReleased(sf::Keyboard::Key key) {return false;}



KeyboardHandler::KeyboardHandler() {}

void KeyboardHandler::addKeyboardListener(AbstractKeyboardListener* listener) {
    this->listeners.push_back(listener);
}

void KeyboardHandler::removeKeyboardListener(const AbstractKeyboardListener* listener) {
    auto it = std::find(this->listeners.begin(), this->listeners.end(), listener);
    if (it != this->listeners.end()) {
        this->listeners.erase(it);
    }
}

void KeyboardHandler::callKeyPressedListeners(sf::Keyboard::Key key) {
    for (auto& l : this->listeners) {
        if (l->getActive()) {
            bool result = l->onKeyPressed(key);
            if (result) {
                break;
            }
        }
    }
}

void KeyboardHandler::callKeyReleasedListeners(sf::Keyboard::Key key) {
    for (auto& l : this->listeners) {
        if (l->getActive()) {
            bool result = l->onKeyReleased(key);
            if (result) {
                break;
            }
        }
    }
}