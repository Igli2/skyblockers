#include <algorithm>
#include <iostream>

#include "mouse.hpp"

AbstractMouseListener::AbstractMouseListener(): isActive{true} {}

void AbstractMouseListener::setActive(bool state) {
    this->isActive = state;
}

const bool& AbstractMouseListener::getActive() {
    return this->isActive;
}

bool AbstractMouseListener::onLeftClick(const sf::Vector2i& mousePos) {return false;}
bool AbstractMouseListener::onLeftClickReleased(const sf::Vector2i& mousePos) {return false;}
bool AbstractMouseListener::onRightClick(const sf::Vector2i& mousePos) {return false;}
bool AbstractMouseListener::onRightClickReleased(const sf::Vector2i& mousePos) {return false;}
bool AbstractMouseListener::onMouseMove(const sf::Vector2i& mousePos) {return false;}



MouseHandler::MouseHandler(): states{false, false, false} {}

void MouseHandler::addMouseListener(AbstractMouseListener* b) {
    this->listeners.push_back(b);
}

void MouseHandler::removeMouseListener(const AbstractMouseListener* b) {
    auto it = std::find(this->listeners.begin(), this->listeners.end(), b);
    if (it != this->listeners.end()) {
        this->listeners.erase(it);
    }
}

void MouseHandler::onButtonPressed(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->states[0]) {
        this->states[0] = true;
        this->callLeftClickListeners(mousePos, true);
    }
}

void MouseHandler::onButtonReleased(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->states[0]) {
        this->states[0] = false;
        this->callLeftClickListeners(mousePos, false);
    }
}

void MouseHandler::callLeftClickListeners(const sf::Vector2i& mousePos, const bool& pressed) {
    for (AbstractMouseListener* listener : this->listeners) {
        if (listener->getActive()) {
            if (pressed) {
                bool result = listener->onLeftClick(mousePos);
                if (result) {
                    return;
                }
            } else {
                bool result = listener->onLeftClickReleased(mousePos);
                if (result) {
                    return;
                }
            }
        }
    }
}

void MouseHandler::callMouseMoveListeners(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    for (AbstractMouseListener* listener : this->listeners) {
        if (listener->getActive()) {
            bool result = listener->onMouseMove(mousePos);
            if (result) {
                return;
            }
        }
    }
}