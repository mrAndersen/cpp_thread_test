#ifndef THREAD_TEST_NODE_H
#define THREAD_TEST_NODE_H

#include <cmath>
#include <Graphics/Text.hpp>
#include <Graphics/CircleShape.hpp>
#include <Graphics/RenderWindow.hpp>
#include "S.h"

class Node {
    sf::CircleShape shape;
    sf::Text threadIndexText;
    sf::Vector2f position;

    float speed = 80;
    float radius = 5;
    int angle = 90;
public:
    Node(float radius, const sf::Vector2f &position);

    void update(int &frameTimeMilliseconds, int &threadIndex);

    void draw();
};


#endif //THREAD_TEST_NODE_H
