/*
TODO's:
 # remove test code in guihandler.cpp
 - add selected item to inventory, follows mouse, visible when inventory closed
 - load / save inventory data
 - inventory with resources (GUI)
 - block placement / destruction
 - item list with all unlocked items (GUI)
 - crafting (GUI) (same as resource list inv?)
 - in ResourceManager: manage playerdata, load sounds
 - block states for block data (util.hpp)
 - world: unlocked area handling (buy with materials, vector with area data structs, 4x4 block areas)
 - create new world (set start blocks, add first area to unlocked ones)
 - block placement in unlocked area only
 - in World::renderChunks(): render chunks only if visible on screen
 - block ticks
 - zooming with mouse wheel
 - in KeyboardHandler::addKeyboardListener(): priority: default 0 push_back, 1 or higher insert with "quick sort search"
 - in MouseHandler::addMouseListener(): priority: default 0 push_back, 1 or higher insert with "quick sort search"
Controls:
 - WSAD: scrolling
 - R: resources menu
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "resource/resource_manager.hpp"
#include "world/world.hpp"
#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "gui/gui_handler.hpp"

class Main {
    private:
        sf::RenderWindow window;
        bool running;
        ResourceManager resourceManager;
        KeyboardHandler keyboardHandler;
        MouseHandler mouseHandler;
        GUIHandler guiHandler;
        World world;

    public:
        Main();
        void run();
        void updateSize();
        void saveAll();
};