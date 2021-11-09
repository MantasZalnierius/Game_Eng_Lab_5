#include "Game.h"

int main(int argc, char** argv)
{
	Game* game = new Game("LAB 5", 100, 100, 1200, 1000, SDL_WINDOW_INPUT_FOCUS);
    game->run();
    return 1;
}