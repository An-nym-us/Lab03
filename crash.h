#pragma once

#include "gameState.h"
class Crash
{
public:
    bool landerCrashed(GameState* GameStateInstance);


private:
    double altitudeToGround(Ground groundInstance, GameState* GameStateInstance);
    bool crashedIntoGroundCheck(GameState* GameStateInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* GameStateInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty(GameState* GameStateInstance);

};
