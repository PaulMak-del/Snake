#include "Game.h"


const int TURNING_TIME = 100;

Game::Game(int width, int height) {
    this->window.create(sf::VideoMode(width, height), "Snake", sf::Style::Default);
    this->window.setVerticalSyncEnabled(true);
    this->window.setFramerateLimit(10);
    this->score = 1;
    this->state = MENU;
}

void Game::menu() {
    sf::Event event{};
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window.close();
    }

    sf::Text menu_text;
    menu_text.setString("PRESS 'SPACE' TO START");
    menu_text.setFillColor(sf::Color::White);
    menu_text.setFont(this->font);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->state = GAME_LOOP;
    }

    this->window.clear();
    this->window.draw(menu_text);
    this->window.display();

}

void Game::game_over() {
    sf::Event event{};
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window.close();
    }

    sf::Text game_over_text;
    game_over_text.setString("PRESS \"ENTER\" TO RESTART\n"
                             "YOUR SCORE: " + std::to_string(this->score) +
                             "\nSURVIVING TIME: " + this->time.getString());
    game_over_text.setFont(this->font);
    game_over_text.setFillColor(sf::Color::White);
    game_over_text.setCharacterSize(50);
    game_over_text.setPosition(0, 100);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        init();
        this->state = GAME_LOOP;
    }

    this->window.clear();
    draw();
    this->window.draw(game_over_text);
    this->window.display();
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
    this->clock.restart();

    this->food.clear();
    this->food.push_back(this->goodBerriesFactory.createFood());

    this->snake.setPosition(100, 100);
    this->snake.revive();
}

void Game::game_loop() {
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
    } else {
        this->state = GAME_OVER;
    }
    if (snake.checkCollision()) {
        snake.kill();
    }
    //-------------------------------------------------------
    //-----------------Feeding_snake-------------------------
    for (auto & i : food) {
        if (getDistance(snake.getPosition(), i->getPosition()) <= snake.getRadius() + i->getRadius()) {
            i->eaten(&window, &snake);
            //______Bad, very bad thing_____
            if (typeid(GoodBerries) == typeid(*i)) {
                score++;
                string_score.setString("SCORE: " + std::to_string(score));
            }
            if (typeid(BadBerries) == typeid(*i)) {
                score--;
                string_score.setString("SCORE: " + std::to_string(score));
            }
        }
    }

    this->window.clear();
    this->draw();
    window.display();
}

void Game::draw() {
    this->window.draw(string_score);
    this->window.draw(time);
    for (int i = this->food.size() - 1; i >= 0; --i) {
        food[i]->draw(&window);
    }
    snake.draw(&window);
}

void Game::key_processing() {
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
}