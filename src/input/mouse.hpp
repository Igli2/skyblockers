#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class AbstractMouseListener {
    private:
        bool isActive;

    public:
        AbstractMouseListener();
        void setActive(bool state);
        const bool& getActive();
        virtual bool onLeftClick(const sf::Vector2i& mousePos);
        virtual bool onLeftClickReleased(const sf::Vector2i& mousePos);
        virtual bool onRightClick(const sf::Vector2i& mousePos);
        virtual bool onRightClickReleased(const sf::Vector2i& mousePos);
        virtual bool onMouseMove(const sf::Vector2i& mousePos);
};

class MouseHandler {
    private:
        std::vector<AbstractMouseListener*> listeners;
        bool states[3];

    public:
        MouseHandler();
        void addMouseListener(AbstractMouseListener* b);
        void removeMouseListener(const AbstractMouseListener* b);
        void onButtonPressed(const sf::Event& event, const sf::RenderWindow& window);
        void onButtonReleased(const sf::Event& event, const sf::RenderWindow& window);
        void callLeftClickListeners(const sf::Vector2i& mousePos, const bool& pressed);
        void callMouseMoveListeners(const sf::RenderWindow& window);
};