#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class AbstractKeyboardListener {
    private:
        bool isActive;

    public:
        AbstractKeyboardListener();
        void setActive(bool state);
        const bool& getActive();
        virtual bool onKeyPressed(sf::Keyboard::Key key);
        virtual bool onKeyReleased(sf::Keyboard::Key key);
};

class KeyboardHandler {
    private:
        std::vector<AbstractKeyboardListener*> listeners;

    public:
        KeyboardHandler();
        void addKeyboardListener(AbstractKeyboardListener* listener);
        void removeKeyboardListener(const AbstractKeyboardListener* listener);
        void callKeyPressedListeners(sf::Keyboard::Key key);
        void callKeyReleasedListeners(sf::Keyboard::Key key);
};