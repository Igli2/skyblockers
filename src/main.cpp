#include <iostream>

#include "main.hpp"

Main::Main(): window(sf::VideoMode(600, 600), "Skyblockers"), world{&this->keyboardHandler, &this->guiHandler}, guiHandler{&this->mouseHandler, &this->keyboardHandler} {
    this->window.setFramerateLimit(60);
}

void Main::run() {
    this->running = true;
    while (running && this->window.isOpen()) {
        sf::Event event;
        while (this->window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    this->running = false;
                    return;
                case sf::Event::Resized:
                    this->updateSize();
                    break;
                case sf::Event::MouseButtonPressed:
                    this->mouseHandler.onButtonPressed(event, this->window);
                    break;
                case sf::Event::MouseButtonReleased:
                    this->mouseHandler.onButtonReleased(event, this->window);
                    break;
                case sf::Event::KeyPressed:
                    this->keyboardHandler.callKeyPressedListeners(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    this->keyboardHandler.callKeyReleasedListeners(event.key.code);
                    break;
                case sf::Event::MouseMoved:
                    this->mouseHandler.callMouseMoveListeners(this->window);
                    break;
            }
        }

        this->window.clear(sf::Color::White);

        this->resourceManager.tick();
        this->world.renderChunks(this->window, this->resourceManager);
        this->guiHandler.render(this->window, this->resourceManager);

        this->window.display();
    }
}

void Main::updateSize() {
    float width = this->window.getSize().x;
    float height = this->window.getSize().y;

    sf::View view = this->window.getDefaultView();
    view.setSize(width, height);
    view.setCenter(width / 2, height / 2);
    this->window.setView(view);
}

void Main::saveAll() {
    this->world.saveAll();
}

int main() {
    Main app;
    app.run();
    app.saveAll();
}