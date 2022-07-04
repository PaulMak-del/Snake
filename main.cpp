/*
 * ----TODO----
 * 1. Add bad berries (that makes snake smaller) --DONE
 * 2. Add poisoned berries (snake dies) -----------DONE
 * 3. Food can spawn in other objects
 * 4. Add menu
 * 4.1. Add restart button
 * 5. Add timer and increasing complexity ---------DONE
 * 6. Add new feature (like walls, mice or
 *                      tricks with tail)
 * 7. Should I create 'game' class for window creating?
 *    Then I can put 'game' object in methods and get access to window size or score
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include "drawable/Snake.h"
#include "myMath.h"
#include "drawable/Berries.h"

const int TURNING_TIME = 100;

int main() {
    int width = 800;
    int height = 600;

    sf::RenderWindow window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(10);

    //Score
    int num_score = 1;
    sf::Text string_score;
    sf::Text time;
    sf::Font font;
    if (!font.loadFromFile(R"(D:\Projects\C++\Snake\font.ttf)")) {
        std::cout << "FONT NOT FOUND\n";
    }
    string_score.setFont(font);
    string_score.setString("SCORE: " + std::to_string(num_score));
    string_score.setFillColor(sf::Color::White);
    string_score.setCharacterSize(24);
    time.setFont(font);
    time.setCharacterSize(25);
    time.setFillColor(sf::Color::White);
    time.setPosition(width - 200, 0);

    Snake snake;

    auto* goodBerriesFactory = new GoodBerriesFactory;
    auto* badBerriesFactory = new BadBerriesFactory;
    auto* poisonedBerriesFactory = new PoisonedBerriesFactory;

    std::vector<Food*> food;
    food.push_back(goodBerriesFactory->createFood());

    sf::Clock clock;
    sf::Clock lastTurn;

    while (window.isOpen()) {
        //---Clock---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //------------------Increasing_Complexity----------------
        if (clock.getElapsedTime().asMilliseconds() % 10000 > 0 && clock.getElapsedTime().asMilliseconds() % 10000 < 100) {
            food.push_back(badBerriesFactory->createFood());
        }
        if (clock.getElapsedTime().asMilliseconds() % 20000 > 0 && clock.getElapsedTime().asMilliseconds() % 20000 < 100) {
            food.push_back(poisonedBerriesFactory->createFood());
        }
        //-------------------------------------------------------
        //------------------KEYBOARD_EVENTS----------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        //Use for checking correctness
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            food.push_back(badBerriesFactory->createFood());
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
            time.setString(std::to_string(clock.getElapsedTime().asSeconds()));
        }
        if (snake.checkCollision()) {
            snake.kill();
        }
        //-------------------------------------------------------
        //-----------------Feeding_snake-------------------------
        for (int i = 0; i < food.size(); i++) {
            if (getDistance(snake.getPosition(), food[i]->getPosition()) <= snake.getRadius() + food[i]->getRadius()) {
                food[i]->eaten(&window, &snake);
                //______Bad, very bad thing_____
                if (typeid(GoodBerries) == typeid(*food[i])) {
                    num_score++;
                    string_score.setString("SCORE: " + std::to_string(num_score));
                }
                if (typeid(BadBerries) == typeid(*food[i])) {
                    num_score--;
                    string_score.setString("SCORE: " + std::to_string(num_score));
                }
            }
        }
        //-------------------------------------------------------

        window.clear();
        window.draw(string_score);
        window.draw(time);
        for (int i = 0; i < food.size(); i++) {
            food[i]->draw(&window);
        }
        snake.draw(&window);
        window.display();
    }

    return 0;
}

