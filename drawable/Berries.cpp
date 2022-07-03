#include <cmath>
#include "Berries.h"

GoodBerries::GoodBerries(float radius, sf::Color color) : Food(radius, color) {}

void GoodBerries::eaten(sf::RenderWindow* window, Snake* snake) {
    snake->addBlock();
    float randX = round(float((rand() % (window->getSize().x - 25))) / 25.0f) * 25;
    float randY = round(float((rand() % (window->getSize().y - 25))) / 25.0f) * 25;
    this->setPosition(randX, randY);
}

BadBerries::BadBerries(float radius, sf::Color color) : Food(radius, color) {}

void BadBerries::eaten(sf::RenderWindow *window, Snake *snake) {
    snake->removeBlock();
    float randX = round(float((rand() % (window->getSize().x - 25))) / 25.0f) * 25;
    float randY = round(float((rand() % (window->getSize().y - 25))) / 25.0f) * 25;
    this->setPosition(randX, randY);
}

PoisonedBerries::PoisonedBerries(float radius, sf::Color color) : Food(radius, color) {}

void PoisonedBerries::eaten(sf::RenderWindow *window, Snake *snake) {
    snake->kill();
}
