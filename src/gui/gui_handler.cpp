#include "gui_handler.hpp"

GUIHandler::GUIHandler(MouseHandler* mh, KeyboardHandler* kh): mouseHandler{mh}, keyboardHandler{kh} {
    kh->addKeyboardListener(this);
    mh->addMouseListener(&this->inventory);
    kh->addKeyboardListener(&this->inventory);
}

void GUIHandler::addGUI(std::unique_ptr<GUIBase> gui, std::string name) {
    if (!this->guis.contains(name)) {
        this->mouseHandler->addMouseListener(gui.get());
        this->keyboardHandler->addKeyboardListener(gui.get());
        this->guis[name] = std::move(gui);
        this->guiOrder.push_back(name);
    }
}

void GUIHandler::render(sf::RenderWindow& window, ResourceManager& resourceManager, int scrollX, int scrollY) {
    for (auto& [key, value] : this->guis) {
        value->render(window, resourceManager);
    }
    this->inventory.render(window, resourceManager, scrollX, scrollY);
}

bool GUIHandler::onKeyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::Escape) {
        if (this->inventory.isVisible()) {
            this->inventory.setVisible(false);
            return true;
        } else {
            if (!this->guis.empty()) {
                std::string lastName = this->guiOrder.back();
                std::unique_ptr<GUIBase> gui = std::move(this->guis[lastName]);
                this->keyboardHandler->removeKeyboardListener(gui.get());
                this->mouseHandler->removeMouseListener(gui.get());

                this->guis.erase(lastName);
                this->guiOrder.pop_back();

                return true;
            }
        }
    }
    return false;
}

Inventory& GUIHandler::getInventory() {
    return this->inventory;
}