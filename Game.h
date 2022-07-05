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

    void draw();
    void key_processing();
public:
    enum GameState state;
    sf::RenderWindow window;

    Game(int width, int height);
    void init();
    void menu();
    void game_loop();
    void game_over();
};


#endif //JUMP_GAME_H
