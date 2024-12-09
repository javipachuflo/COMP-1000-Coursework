#include "Game.h"

int main()
{
    Game game;

    while (game.Update()) {
        // Game loop continues as long as Update returns true
    }

    return 0;
}