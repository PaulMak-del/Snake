#include "Snake.h"
#include "../myMath.h"

Snake::Snake() {
    this->size = 5;
    this->speed = 12;
    this->dir = RIGHT;
    for (int i = 0; i < this->size; i++) {
        snake[i].block = sf::CircleShape(12.0f);
        snake[i].block.setOrigin(snake[i].block.getRadius() / 2, snake[i].block.getRadius() / 2);
        snake[i].block.setPosition(sf::Vector2f(500.0f - 24.0f * i, 500.0f));
        snake[i].block.setFillColor(sf::Color::Green);
    }
}

void Snake::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < this->size; i++) {
        window->draw(snake[i].block);
    }
}

void Snake::move(sf::RenderWindow *window)
{
    for (int i = this->size - 1; i > 0; --i) {
        this->snake[i].block.setPosition(this->snake[i-1].block.getPosition());
    }

    switch (this->dir) {
        case RIGHT:
            this->snake[0].block.move(this->speed, 0.0f);
            break;
        case LEFT:
            this->snake[0].block.move(-this->speed, 0.0f);
            break;
        case UP:
            this->snake[0].block.move(0.0f, -this->speed);
            break;
        case DOWN:
            this->snake[0].block.move(0.0f, this->speed);
            break;
    }

    for (int i = 0; i < this->size; ++i) {
        if (this->snake[i].block.getPosition().x >= window->getSize().x) {
            this->snake[i].block.setPosition(0, this->snake[i].block.getPosition().y);
        }
        if (this->snake[i].block.getPosition().y >= window->getSize().y) {
            this->snake[i].block.setPosition(this->snake[i].block.getPosition().x, 0);
        }
        if (this->snake[i].block.getPosition().x < 0) {
            this->snake[i].block.setPosition(window->getSize().x, this->snake[i].block.getPosition().y);
        }
        if (this->snake[i].block.getPosition().y < 0) {
            this->snake[i].block.setPosition(this->snake[i].block.getPosition().x, window->getSize().y);
        }
    }
}

sf::Vector2f Snake::getPosition() {
    return this->snake[0].block.getPosition();
}

void Snake::setDirection(enum Direction dir) {
    this->dir = dir;
}

void Snake::addBlock() {
    if (this->size >= 200) {
        // segmentation fault
        return;
    }
    this->snake[size].block = sf::CircleShape(12.0f);
    this->snake[size].block.setOrigin(this->snake[size].block.getRadius() / 2, this->snake[size].block.getRadius() / 2);
    this->snake[size].block.setPosition(this->snake[size - 1].block.getPosition());
    this->snake[size].block.setFillColor(sf::Color::Green);
    this->snake[size + 1].block = sf::CircleShape(12.0f);
    this->snake[size + 1].block.setOrigin(this->snake[size].block.getRadius() / 2, this->snake[size].block.getRadius() / 2);
    this->snake[size + 1].block.setPosition(this->snake[size - 1].block.getPosition());
    this->snake[size + 1].block.setFillColor(sf::Color::Green);
    this->size += 2;
}

enum Direction Snake::getDirection() {
    return this->dir;
}

bool Snake::checkCollision() {
    bool over = false;
    for (int i = 1; i < this->size; ++i) {
        if (getDistance(this->snake[0].block.getPosition(), this->snake[i].block.getPosition()) <= 5) {
            over = true;
            break;
        }
    }
    return over;
}

void Snake::kill() {
    for (int i = 0; i < this->size; i++) {
        this->snake[i].block.setFillColor(sf::Color::Red);
    }
}
