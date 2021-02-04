#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "gui_base.hpp"
#include "../resource/blocks.hpp"
#include "../resource/resource_manager.hpp"

class Inventory: public GUIBase {
    private:
        std::map<Blocks, uint> itemCount;
        sf::RectangleShape slot;
        sf::Text text;
        bool visible;

    public:
        Inventory();
        virtual void render(sf::RenderWindow& window, ResourceManager& resourceManager) override;
        virtual bool onLeftClick(const sf::Vector2i& mousePos) override;
        void addItem(Blocks id, uint amount);
        void setVisible(bool state);
        const bool& isVisible();
};