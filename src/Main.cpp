#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    std::cout << "SOMETHING WRONG WITH TIME";
    srand(static_cast<unsigned>(time(nullptr)));
	Game* game = new Game("LAB 5", 100, 100, 1200, 1000, SDL_WINDOW_INPUT_FOCUS);
    game->run();
    return 0;
}