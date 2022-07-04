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

#include "Game.h"

int main() {
    int width = 800;
    int height = 600;
    Game game(width, height);

    switch(game.state) {
        case MENU:
            //pass
            break;
        case GAME_LOOP:
            game.game_run();
            break;
        case GAME_OVER:
            //pass
            break;
    }

    return 0;
}

