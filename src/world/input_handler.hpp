#pragma once

#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../gui/gui_handler.hpp"

class World;

class InputHandler: public AbstractKeyboardListener, public AbstractMouseListener {
    private:
        const int scrollSpeed = 4;

        bool pressed[4];
        bool isBreakingBlock;
        int breakingBlockX;
        int breakingBlockY;
        uint breakingBlockTimer;
        GUIHandler* guiHandler;
        World* world;

    public:
        int scrollX;
        int scrollY;

        InputHandler(MouseHandler* mouseHandler, KeyboardHandler* keyboardHandler, GUIHandler* guiHandler, World* world);
        virtual bool onKeyPressed(sf::Keyboard::Key key) override;
        virtual bool onKeyReleased(sf::Keyboard::Key key) override;
        virtual bool onLeftClick(const sf::Vector2i& mousePos) override;
        virtual bool onLeftClickReleased(const sf::Vector2i& mousePos) override;
        virtual bool onMouseMove(const sf::Vector2i& mousePos) override;
        void updateScroll(sf::Vector2i mousePos);
        void updateIsBreakingBlock(sf::Vector2i mousePos);
        void tick();
};