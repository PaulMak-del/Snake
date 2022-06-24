//
// Created by pawel on 16.06.2022.
//

#include "Snake.h"
#include "myMath.h"

Snake::Snake()
{
    this->size = 5;
    this->speed = 25;
    for (int i = 0; i < this->size; i++) {
        snake[i].block = sf::RectangleShape(sf::Vector2f(25.0f, 25.0f));
        snake[i].block.setPosition(sf::Vector2f(500.0f - 25.0f * i, 500.0f));
        snake[i].block.setFillColor(sf::Color::Green);
        snake[i].dir = RIGHT;
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
    for (int i = 0; i < this->size; i++) {
        switch (this->snake[i].dir) {
            case RIGHT:
                this->snake[i].block.move(this->speed, 0.0f);
                break;
            case LEFT:
                this->snake[i].block.move(-this->speed, 0.0f);
                break;
            case UP:
                this->snake[i].block.move(0.0f, -this->speed);
                break;
            case DOWN:
                this->snake[i].block.move(0.0f, this->speed);
                break;
        }
    }

    for (int i = this->size - 1; i > 0; --i) {
        this->snake[i].dir = this->snake[i-1].dir;
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

sf::Vector2f Snake::getPosition()
{
    return this->snake[0].block.getPosition();
}

void Snake::setDirection(enum Direction dir)
{
    this->snake[0].dir = dir;
}

void Snake::addBlock()
{
    if (this->size >= 99) {
        // segmentation fault
        return;
    }
    this->snake[size].block = sf::RectangleShape(sf::Vector2f(25.0f, 25.0f));
    this->snake[size].block.setPosition(this->snake[size-1].block.getPosition());
    this->snake[size].block.setFillColor(sf::Color::Green);
    this->snake[size].dir = RIGHT;
    switch (this->snake[size-1].dir) {
        case RIGHT:
            this->snake[size].dir = RIGHT;
            this->snake[size].block.move(-25.0f, 0.0f);
            break;
        case LEFT:
            this->snake[size].dir = LEFT;
            this->snake[size].block.move(25.0f, 0.0f);
            break;
        case UP:
            this->snake[size].dir = UP;
            this->snake[size].block.move(0.0f, 25.0f);
            break;
        case DOWN:
            this->snake[size].dir = DOWN;
            this->snake[size].block.move(0.0f, -25.0f);
            break;
    }
    this->size++;
}

enum Direction Snake::getDirection()
{
    return this->snake[0].dir;
}

bool Snake::checkCollision()
{
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
