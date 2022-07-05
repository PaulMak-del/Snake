#ifndef JUMP_SNAKE_H
#define JUMP_SNAKE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum Direction
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

struct SnakeBlock {
    sf::CircleShape block;
};

class Snake {
private:
    int size;
    float speed;
    enum Direction dir;
    bool alive;
    struct SnakeBlock snake[201];
public:
    Snake();
    void draw(sf::RenderWindow *window);
    void move(sf::RenderWindow *window);
    void setDirection(enum Direction dir);
    void addBlock();
    void removeBlock();
    enum Direction getDirection();
    sf::Vector2f getPosition();
    void setPosition(int x, int y);
    void setPosition(sf::Vector2f v);
    bool checkCollision();
    void kill();
    void revive();
    bool isAlive();
    float getRadius();
};


#endif //JUMP_SNAKE_H
