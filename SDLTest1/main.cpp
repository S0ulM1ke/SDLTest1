#include <iostream>
#include "Game.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[])
{
    Game game;
    game.gameLoop();

    return 0;
}