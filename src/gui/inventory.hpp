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
        Blocks selectedItem;

    public:
        Inventory();
        virtual void render(sf::RenderWindow& window, ResourceManager& resourceManager, int scrollX, int scrollY);
        virtual bool onLeftClick(const sf::Vector2i& mousePos) override;
        virtual bool onRightClick(const sf::Vector2i& mousePos) override;
        void addItem(Blocks id, uint amount);
        bool removeItem(Blocks id, uint amount);
        void setVisible(bool state);
        const bool& isVisible();
        const Blocks& getSelectedItem();
        void save();
        void load();
};