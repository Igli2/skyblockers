#include <iostream>
#include <memory>
#include <cmath>

#include "input_handler.hpp"
#include "world.hpp"
#include "../gui/inventory.hpp"
#include "../resource/blocks.hpp"

InputHandler::InputHandler(MouseHandler* mouseHandler, KeyboardHandler* keyboardHandler, GUIHandler* guiHandler, World* world):
    scrollX{300},
    scrollY{300},
    guiHandler{guiHandler},
    world{world},
    isBreakingBlock{false},
    breakingBlockTimer{0},
    pressed{false} {
        keyboardHandler->addKeyboardListener(this);
        mouseHandler->addMouseListener(this);
}

bool InputHandler::onKeyPressed(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::W:
            this->pressed[0] = true;
            return true;
        case sf::Keyboard::Key::S:
            this->pressed[1] = true;
            return true;
        case sf::Keyboard::Key::A:
            this->pressed[2] = true;
            return true;
        case sf::Keyboard::Key::D:
            this->pressed[3] = true;
            return true;
        case sf::Keyboard::Key::R:
            this->guiHandler->getInventory().setVisible(true);
            return true;
    }
    return false;
}

bool InputHandler::onKeyReleased(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::W:
            this->pressed[0] = false;
            return true;
        case sf::Keyboard::Key::S:
            this->pressed[1] = false;
            return true;
        case sf::Keyboard::Key::A:
            this->pressed[2] = false;
            return true;
        case sf::Keyboard::Key::D:
            this->pressed[3] = false;
            return true;
    }
    return false;
}

void InputHandler::updateScroll(sf::Vector2i mousePos) {
    if (this->pressed[0]) {
        this->scrollY += this->scrollSpeed;
        this->updateIsBreakingBlock(mousePos);
    }
    if (this->pressed[1]) {
        this->scrollY -= this->scrollSpeed;
        this->updateIsBreakingBlock(mousePos);
    }
    if (this->pressed[2]) {
        this->scrollX += this->scrollSpeed;
        this->updateIsBreakingBlock(mousePos);
    }
    if (this->pressed[3]) {
        this->scrollX -= this->scrollSpeed;
        this->updateIsBreakingBlock(mousePos);
    }
}

bool InputHandler::onLeftClick(const sf::Vector2i& mousePos) {
    int blockX = std::floor(((float)mousePos.x - (float)this->scrollX) / 32);
    int blockY = std::floor(((float)mousePos.y - (float)this->scrollY) / 32);

    if (this->guiHandler->getInventory().getSelectedItem() != Blocks::AIR) {
        if (this->world->getBlock(blockX, blockY).blockType == Blocks::AIR) {
            this->world->setBlock(blockX, blockY, this->guiHandler->getInventory().getSelectedItem());
            this->guiHandler->getInventory().removeItem(this->guiHandler->getInventory().getSelectedItem(), 1);
            if (!this->guiHandler->getInventory().hasItem(this->guiHandler->getInventory().getSelectedItem(), 1)) {
                this->guiHandler->getInventory().setSelectedItem(Blocks::AIR);
            }
        }
    } else {
        this->isBreakingBlock = true;
        this->breakingBlockX = blockX;
        this->breakingBlockY = blockY;
    }
    return true;
}

bool InputHandler::onLeftClickReleased(const sf::Vector2i& mousePos) {
    if (this->isBreakingBlock) {
        this->isBreakingBlock = false;
        this->breakingBlockTimer = 0;
        return true;
    }
    return false;
}

void InputHandler::updateIsBreakingBlock(sf::Vector2i mousePos) {
    if (this->isBreakingBlock) {
        int blockX = std::floor(((float)mousePos.x - (float)this->scrollX) / 32);
        int blockY = std::floor(((float)mousePos.y - (float)this->scrollY) / 32);

        if (this->breakingBlockX != blockX || this->breakingBlockY != blockY) {
            this->isBreakingBlock = false;
            this->breakingBlockTimer = 0;
        }
    }
}

bool InputHandler::onMouseMove(const sf::Vector2i& mousePos) {
    this->updateIsBreakingBlock(mousePos);
    return false;
}

void InputHandler::tick(ResourceManager& manager) {
    if (this->isBreakingBlock) {
        this->breakingBlockTimer += 1;
        if (this->breakingBlockTimer > 120) {
            try {
                BlockData brokenBlock = this->world->getBlock(this->breakingBlockX, this->breakingBlockY);
                if (brokenBlock.blockType != Blocks::AIR) {
                    std::map<Blocks, int> drops = manager.getBlockClass(brokenBlock.blockType)->getDrops(brokenBlock);
                    for (const auto& [blockId, amount] : drops) {
                        this->guiHandler->getInventory().addItem(blockId, amount);
                    }
                    this->world->setBlock(this->breakingBlockX, this->breakingBlockY, Blocks::AIR);
                }
            } catch (std::runtime_error& err) {}
        }
    }
}