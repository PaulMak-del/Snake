#ifndef JUMP_GOODBERRIES_H
#define JUMP_GOODBERRIES_H

#include "Food.h"

class GoodBerries : public Food {
public:
    GoodBerries(float radius, sf::Vector2f position, sf::Color color);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};


#endif //JUMP_GOODBERRIES_H
