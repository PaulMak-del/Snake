/*
 * ----TODO----
 * 1. Add bad berries (that makes snake smaller)
 * 2. Add poisoned berries (snake dies)
 * 3. Add mice (they run away from snake)
 * 4. Problem with "food" that can spawn in the snake
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "drawable/Snake.h"
#include "myMath.h"
#include "drawable/GoodBerries.h"

const int TURNING_TIME = 100;

int main() {
    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);

    Snake snake;

    GoodBerries good_ber(12.0f, sf::Vector2f(600, 400), sf::Color::Blue);

    sf::Clock clock;
    sf::Clock lastTurn;

    while (window.isOpen()) {
        //---Clock---
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //------------------KEYBOARD_EVENTS----------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (snake.getDirection() != LEFT && lastTurn.getElapsedTime().asMilliseconds() > TURNING_TIME) {
                lastTurn.restart();
                snake.setDirection(RIGHT);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (snake.getDirection() != RIGHT && lastTurn.getElapsedTime().asMilliseconds() > TURNING_TIME) {
                lastTurn.restart();
                snake.setDirection(LEFT);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (snake.getDirection() != DOWN && lastTurn.getElapsedTime().asMilliseconds() > TURNING_TIME) {
                lastTurn.restart();
                snake.setDirection(UP);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (snake.getDirection() != UP && lastTurn.getElapsedTime().asMilliseconds() > TURNING_TIME) {
                lastTurn.restart();
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
        if (getDistance(snake.getPosition(), good_ber.getPosition()) <= 12.0f + good_ber.getRadius()) {
            good_ber.eaten(&window, &snake);
        }
        //-------------------------------------------------------
        //----------Check_the_game_over---------------------------
        //-------------------------------------------------------

        window.clear();
        snake.draw(&window);
        good_ber.draw(&window);
        window.display();
    }

    return 0;
}

