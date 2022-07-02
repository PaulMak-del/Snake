#ifndef JUMP_BERRIES_H
#define JUMP_BERRIES_H

#include "Food.h"

class GoodBerries : public Food {
public:
    GoodBerries(float radius, sf::Vector2f position, sf::Color color);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

class BadBerries : public Food{
public:
    BadBerries(float radius, sf::Vector2f v, sf::Color color);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

class PoisonedBerries : public Food {
public:
    PoisonedBerries(float radius, sf::Vector2f v, sf::Color color);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

#endif //JUMP_BERRIES_H
