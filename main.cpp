#include <iostream>
#include <Window.hpp>
#include "src/Node.h"

int main() {
    S::font.loadFromFile("resources/OpenSans-Regular.ttf");

    S::window = new sf::RenderWindow(sf::VideoMode(1200, 800), "?");
    S::window->setActive(false);

    sf::Clock drawFpsClock;
    sf::Event e{};

    for (int i = 0; i < S::concurrency; ++i) {
        std::thread thread(&S::refresh, i);
        thread.detach();
    }

    while (S::window->isOpen()) {
        if (S::secondFrameClock.getElapsedTime().asSeconds() >= 1) {
            S::secondFrameClock.restart();
            std::string title;

            title += "FPS:" + std::to_string(S::FPS) + " [";
            S::FPS = 0;

            for (int i = 0; i < S::concurrency; ++i) {
                title += std::to_string(S::threadUPS[i]) + ",";
                S::threadUPS[i] = 0;
            }

            title += "]";
            S::window->setTitle(title);
        } else {
            S::FPS++;
        }

        while (S::window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                S::window->close();
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                auto mouse = sf::Mouse::getPosition(*S::window);

                for (int i = 0; i < 10; ++i) {
                    auto n = new Node(10, {(float) mouse.x + i * 15, (float) mouse.y});
                }


            }
        }

        S::window->clear(sf::Color(230, 230, 230));
        S::redraw();
        S::window->display();

//        if (S::threadsReady()) {
//
//            S::resetThreads();
//        }
    }


    return EXIT_SUCCESS;
}