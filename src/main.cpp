#include "engine-core/game-engine/engine.h"
#include "stdio.h"

int main(int argc, char* argv[]) {
    HiddenEngine gameEngine;
    
    if(!gameEngine.Initialize()) 
        return 0;

    gameEngine.GetInfo();
    gameEngine.Run();
    gameEngine.Shutdown();
    
   return 0;
}