#include "Game.h"


const int TURNING_TIME = 100;

Game::Game(int width, int height) {
    this->window.create(sf::VideoMode(width, height), "Snake", sf::Style::Default);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(10);
    this->state = GAME_LOOP;
}

void Game::init() {
    this->score = 1;
    if (!this->font.loadFromFile(R"(D:\Projects\C++\Snake\font.ttf)")) {
        std::cout << "FONT NOT FOUND\n";
    }
    this->string_score.setFont(font);
    this->string_score.setString("SCORE: " + std::to_string(this->score));
    this->string_score.setFillColor(sf::Color::White);
    this->string_score.setCharacterSize(24);
    this->time.setFont(font);
    this->time.setCharacterSize(25);
    this->time.setFillColor(sf::Color::White);
    this->time.setPosition(this->window.getSize().x - 200, 0);

    this->food.push_back(this->goodBerriesFactory.createFood());
}

void Game::game_loop() {
    //---Clock---
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window.close();
    }

    //------------------Increasing_Complexity----------------
    if (clock.getElapsedTime().asMilliseconds() % 10000 > 0 && clock.getElapsedTime().asMilliseconds() % 10000 < 100) {
        food.push_back(badBerriesFactory.createFood());
    }
    if (clock.getElapsedTime().asMilliseconds() % 20000 > 0 && clock.getElapsedTime().asMilliseconds() % 20000 < 100) {
        food.push_back(poisonedBerriesFactory.createFood());
    }
    //-------------------------------------------------------
    //------------------KEYBOARD_EVENTS----------------------
    key_processing();
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
                score++;
                string_score.setString("SCORE: " + std::to_string(score));
            }
            if (typeid(BadBerries) == typeid(*food[i])) {
                score--;
                string_score.setString("SCORE: " + std::to_string(score));
            }
        }
    }

    this->draw();
}

void Game::draw() {
    this->window.clear();
    this->window.draw(string_score);
    this->window.draw(time);
    for (int i = 0; i < food.size(); i++) {
        food[i]->draw(&window);
    }
    snake.draw(&window);
    window.display();
}

void Game::game_run() {
    init();
    while (this->window.isOpen()) {
        game_loop();
    }
}

void Game::key_processing() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    //Use for checking correctness
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        food.push_back(badBerriesFactory.createFood());
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
}