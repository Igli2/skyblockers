#pragma once

#include <SFML/Graphics.hpp>

#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../resource/resource_manager.hpp"

class GUIBase: public AbstractMouseListener, public AbstractKeyboardListener {
    public:
        GUIBase();
        virtual void render(sf::RenderWindow& window, ResourceManager& resourceManager);
};