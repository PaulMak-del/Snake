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
    struct SnakeBlock snake[201];
public:
    Snake();
    void draw(sf::RenderWindow *window);
    void move(sf::RenderWindow *window);
    void setDirection(enum Direction dir);
    void addBlock();
    enum Direction getDirection();
    sf::Vector2f getPosition();
    bool checkCollision();
    void kill();
};


#endif //JUMP_SNAKE_H
