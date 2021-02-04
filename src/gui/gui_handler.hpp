#pragma once

#include <map>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "gui_base.hpp"
#include "inventory.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"

class GUIHandler: public AbstractKeyboardListener {
    private:
        std::map<std::string, std::unique_ptr<GUIBase>> guis;
        std::vector<std::string> guiOrder;
        MouseHandler* mouseHandler;
        KeyboardHandler* keyboardHandler;
        Inventory inventory;
    
    public:
        GUIHandler(MouseHandler* mouseHandler, KeyboardHandler* keyboardHandler);
        void addGUI(std::unique_ptr<GUIBase> gui, std::string name);
        void render(sf::RenderWindow& window, ResourceManager& resourceManager, int scrollX, int scrollY);
        virtual bool onKeyPressed(sf::Keyboard::Key key) override;
        Inventory& getInventory();
};