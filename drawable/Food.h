#ifndef JUMP_FOOD_H
#define JUMP_FOOD_H


#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Snake.h"

class Food {
private:
    sf::CircleShape food;
public:
    Food(float radius=12.0f, sf::Color color=sf::Color::White);
    void draw(sf::RenderWindow* window);
    sf::Vector2f getPosition();
    float getRadius();
    void setPosition(sf::Vector2f v);
    void setPosition(float x, float y);
    virtual void eaten(sf::RenderWindow* window, Snake* snake);
};


#endif // JUMP_FOOD_H
