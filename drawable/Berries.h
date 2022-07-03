#ifndef JUMP_BERRIES_H
#define JUMP_BERRIES_H

#include "Food.h"

class GoodBerries : public Food {
public:
    GoodBerries(float radius=12.0f, sf::Color color=sf::Color::Blue);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

class BadBerries : public Food{
public:
    BadBerries(float radius=12.0f, sf::Color color=sf::Color::Red);
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

class PoisonedBerries : public Food {
public:
    PoisonedBerries(float radius=12.0f, sf::Color color=sf::Color(0, 255, 255, 255));
    void eaten(sf::RenderWindow* window, Snake* snake) override;
};

//Factories
class FoodFactory {
public:
    virtual Food* createFood() = 0;
    virtual Food* createFood(float, sf::Color) = 0;
    virtual ~FoodFactory() = default;
};

class GoodBerriesFactory : FoodFactory {
public:
    Food* createFood() override {
        return new GoodBerries;
    }
    Food* createFood(float rad, sf::Color color) override {
        return new GoodBerries(rad, color);
    }
};

class BadBerriesFactory : FoodFactory {
public:
    Food* createFood() override {
        return new BadBerries;
    }
    Food* createFood(float rad, sf::Color color) override {
        return new BadBerries(rad, color);
    }
};

class PoisonedBerriesFactory : FoodFactory {
public:
    Food* createFood() override {
        return new PoisonedBerries;
    }
    Food* createFood(float rad, sf::Color color) override {
        return new PoisonedBerries(rad, color);
    }
};


#endif //JUMP_BERRIES_H
