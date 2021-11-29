#include "Game.h"


int main()
{
    Game* Protoype = new Game();
    Protoype->runGame();
    delete Protoype;
    return 0;
}