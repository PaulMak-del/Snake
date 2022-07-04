//
// Created by pawel on 04.07.2022.
//

#ifndef JUMP_GAME_H
#define JUMP_GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "drawable/Snake.h"
#include "drawable/Berries.h"
#include "myMath.h"

enum GameState {
    MENU,
    GAME_LOOP,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    //Score and Time
    int score;
    sf::Text string_score;
    sf::Text time;
    sf::Font font;
    //Clock
    sf::Clock clock;
    sf::Clock lastTurn;
    //Snake
    Snake snake;
    //Factory
    GoodBerriesFactory goodBerriesFactory;
    BadBerriesFactory badBerriesFactory;
    PoisonedBerriesFactory poisonedBerriesFactory;
    //Food
    std::vector<Food*> food;

    void init();
    void game_loop();
    void draw();
    void key_processing();
public:
    enum GameState state;

    Game(int width, int height);
    void menu();
    void game_run();
    void game_over();
};


#endif //JUMP_GAME_H
