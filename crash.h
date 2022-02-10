#pragma once

#include "gameState.h"
class Crash
{
public:


    double altitudeToGround(Ground groundInstance, GameState* landerInstance);
    bool crashedIntoGroundCheck(GameState* landerInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* landerInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty(GameState* GameStateInstance);

};
