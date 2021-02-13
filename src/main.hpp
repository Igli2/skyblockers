/*
Changes:
 + remove item from inventory when placing
 + get block function in world / chunk
 + added block drops to blockdata json
 + added block drops with chances to block singletons
 + get block drops method from block singleton with rng applied
TODO's:
 - item list with all unlocked items (GUI)
 - crafting (GUI) (same as resource list inv?)
 - world: unlocked area handling (buy with materials, vector with area data structs, 4x4 block areas)
 - create new world (set start blocks, add first area to unlocked ones)
 - block placement in unlocked area only
 - in World::renderChunks(): render chunks only if visible on screen
 - sounds
 - zooming with mouse wheel
 - block states for block data (util.hpp)
 - block breaking animation
 - quests
Controls:
 - WSAD: scrolling
 - R: resources menu
 - ESC: close gui
 - LEFT CLICK: place block, hold left click with no item selected: break block
 - RIGHT CLICK: deselect
Notes:
 - bottom texture: scale top texture, -100 brightness for full blocks
 - 2 bottom rows of top texture to top of bottom texture, -100 brightness for flat blocks
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