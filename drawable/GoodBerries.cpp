#include <cmath>
#include "GoodBerries.h"

GoodBerries::GoodBerries(float radius, sf::Vector2f position, sf::Color color) : Food(radius, position, color) {}

void GoodBerries::eaten(sf::RenderWindow* window, Snake* snake) {
    snake->addBlock();
    float randX = round(float((rand() % (window->getSize().x - 25))) / 25.0f) * 25;
    float randY = round(float((rand() % (window->getSize().y - 25))) / 25.0f) * 25;
    this->setPosition(randX, randY);
}
