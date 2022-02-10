#pragma once

#include "gameState.h"
class Crash
{
public:

    bool crashedIntoGroundCheck(GameState* landerInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* landerInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty(GameState* GameStateInstance);


private:

};
