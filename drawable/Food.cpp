#include <iostream>
#include "Food.h"

Food::Food(float radius, sf::Vector2f position, sf::Color color) {
    this->food.setRadius(radius);
    this->food.setFillColor(color);
    this->food.setPosition(position);
    this->food.setOrigin(radius / 2, radius / 2);
}

void Food::draw(sf::RenderWindow* window) {
    window->draw(this->food);
}

void Food::setPosition(sf::Vector2f v) {
    this->food.setPosition(v);
}

void Food::setPosition(float x, float y) {
    this->food.setPosition(x, y);
}

sf::Vector2f Food::getPosition() {
    return this->food.getPosition();
}

float Food::getRadius() {
    return this->food.getRadius();
}

void Food::eaten(sf::RenderWindow *window, Snake *snake) {
    std::cout << "NOTHING\n";
}
