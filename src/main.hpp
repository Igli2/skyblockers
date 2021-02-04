/*
TODO's:
 - block destruction
 - item list with all unlocked items (GUI)
 - crafting (GUI) (same as resource list inv?)
 - world: unlocked area handling (buy with materials, vector with area data structs, 4x4 block areas)
 - create new world (set start blocks, add first area to unlocked ones)
 - block placement in unlocked area only
 - in World::renderChunks(): render chunks only if visible on screen
 - block ticks
 - sounds
 - zooming with mouse wheel
 - block states for block data (util.hpp)
Controls:
 - WSAD: scrolling
 - R: resources menu
 - ESC: close gui
 - LEFT CLICK: place block
 - RIGHT CLICK: deselect
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