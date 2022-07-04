/*
 * --TODO
 * > Update init method (for restarting game)
 * > Food can spawn in other objects
 * > Add menu
 * > Add restart button
 * > Add new feature (like walls, mice or
 *                      tricks with tail)
 * > Should I create 'game' class for window creating?
 *   Then I can put 'game' object in methods and get access to window size or score
 */

#include "Game.h"

int main() {
    int width = 800;
    int height = 600;
    Game game(width, height);
    game.init();

    while(game.window.isOpen()) {
        switch (game.state) {
            case MENU:
                game.menu();
                break;
            case GAME_LOOP:
                game.game_loop();
                break;
            case GAME_OVER:
                game.game_over();
                break;
        }
    }

    return 0;
}

