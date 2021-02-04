#pragma once

#include "../input/keyboard.hpp"
#include "../gui/gui_handler.hpp"

class InputHandler: public AbstractKeyboardListener {
    private:
        const int scrollSpeed = 4;

        bool pressed[4]; //wsad
        GUIHandler* guiHandler;

    public:
        int scrollX;
        int scrollY;

        InputHandler(KeyboardHandler* keyboardHandler, GUIHandler* guiHandler);
        virtual bool onKeyPressed(sf::Keyboard::Key key) override;
        virtual bool onKeyReleased(sf::Keyboard::Key key) override;
        void updateScroll();
};