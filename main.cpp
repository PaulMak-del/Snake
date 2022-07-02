/*
 * ----TODO----
 * 1. Add bad berries (that makes snake smaller) --DONE
 * 2. Add poisoned berries (snake dies) -----------DONE
 * 3. Add mice (they run away from snake)
 * 4. Food can spawn in other objects
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "drawable/Snake.h"
#include "myMath.h"
#include "drawable/Berries.h"
// #include "drawable/BadBerries.h"

const int TURNING_TIME = 100;

int main() {
    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);

    Snake snake;

    GoodBerries good_berries(12.0f, sf::Vector2f(300, 100), sf::Color::Blue);
    BadBerries bad_berries(12.0f, sf::Vector2f(400, 300), sf::Color::Red);
    PoisonedBerries poison(12.0f, sf::Vector2f(100, 200), sf::Color(0, 255, 255, 255));

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
        if (snake.isAlive()) {
            snake.move(&window);
        }
        if (snake.checkCollision()) {
            snake.kill();
        }
        //-------------------------------------------------------
        //-----------------Feeding_snake-------------------------
        if (getDistance(snake.getPosition(), good_berries.getPosition()) <= 12.0f + good_berries.getRadius()) {
            good_berries.eaten(&window, &snake);
        }
        if (getDistance(snake.getPosition(), bad_berries.getPosition()) <= 12.0f + bad_berries.getRadius()) {
            bad_berries.eaten(&window, &snake);
        }
        if (getDistance(snake.getPosition(), poison.getPosition()) <= 12.0f + poison.getRadius()) {
            poison.eaten(&window, &snake);
        }
        //-------------------------------------------------------
        //----------Check_the_game_over---------------------------
        //-------------------------------------------------------

        window.clear();
        good_berries.draw(&window);
        bad_berries.draw(&window);
        poison.draw(&window);
        snake.draw(&window);
        window.display();
    }

    return 0;
}

