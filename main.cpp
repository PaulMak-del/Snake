#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Snake.h"
#include <cmath>
#include "myMath.h"

int main()
{
    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default);    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);

    Snake snake;

    sf::RectangleShape food(sf::Vector2f(25.0f, 25.0f));
    food.setFillColor(sf::Color::Blue);
    food.setPosition(600, 400);

    sf::Clock clock;

    while (window.isOpen())
    {
        //---Clock---
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //------------------KEYBOARD_EVENTS----------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (snake.getDirection() != LEFT) {
                snake.setDirection(RIGHT);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (snake.getDirection() != RIGHT) {
                snake.setDirection(LEFT);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (snake.getDirection() != DOWN) {
                snake.setDirection(UP);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (snake.getDirection() != UP) {
                snake.setDirection(DOWN);
            }
        }
        //-------------------------------------------------------
        //--------Snake_movement---------------------------------
        if (!snake.checkCollision()) {
            snake.move(&window);
        } else {
            snake.kill();
        }
        //-------------------------------------------------------
        //-----------------Feeding_snake-------------------------
        if (getDistance(snake.getPosition(), food.getPosition()) <= 10) {
            snake.addBlock();
            // float randX = rand() % (width - 25);
            float randX = round((rand() % (width - 25)) / 25) * 25;
            float randY = round((rand() % (height - 25)) / 25) * 25;
            // float randY = rand() % (height - 25);
            food.setPosition(randX, randY);
        }
        //-------------------------------------------------------
        //----------Check_the_game_over---------------------------
        //-------------------------------------------------------

        window.clear();
        snake.draw(&window);
        window.draw(food);
        window.display();
    }

    return 0;
}

