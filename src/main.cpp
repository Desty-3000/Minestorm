
#include <raylib.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <cstdlib>
#include <ctime>

#include "game_engine.h"
#include "game_renderer.h"


int main(int argc, char* argv[])
{
    //CLEAN MAIN
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    std::srand((unsigned int)std::time(nullptr));

    InitWindow(640, 800, "MineStorm");
    SetTargetFPS(60);

    {
        GameRenderer gameRenderer;
        GameEngine   gameEngine(&gameRenderer);
    }

    return 0;
}