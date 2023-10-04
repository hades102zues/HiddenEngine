#include "engine-core/game-engine/engine.h"
#include "stdio.h"

int main(int argc, char* argv[]) {
    HiddenEngine gameEngine;
    gameEngine.GetInfo();
    if (gameEngine.Initialize()) {
        gameEngine.Run();
        gameEngine.Shutdown();
    }
   
}