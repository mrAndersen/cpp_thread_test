#include "Node.h"

Node::Node(float radius, const sf::Vector2f &position) : position(position), radius(radius) {
    shape.setPosition(position);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color(124, 59, 106));

    S::add(this);
}

void Node::update(int &frameTimeMilliseconds, int &threadIndex) {
    auto rad = angle * M_PI / 180.f;
    float distance = (float)frameTimeMilliseconds / 1000 * speed;

    position.x = position.x + (float) std::cos(rad) * distance;
    position.y = position.y + (float) std::sin(rad) * distance;

    threadIndexText.setPosition(position);
    threadIndexText.setOrigin(0, radius);
    threadIndexText.setString(std::to_string(threadIndex));
    threadIndexText.setFont(S::font);
    threadIndexText.setCharacterSize(10);

    shape.setPosition(position);
}

void Node::draw() {
    S::window->draw(shape);
    S::window->draw(threadIndexText);
}
