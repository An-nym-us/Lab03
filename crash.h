#pragma once

#include "gameState.h"
class Crash
{
public:
    bool endGame();


private:
    double altitudeToGround(Ground groundInstance, GameState* GameStateInstance);
    bool crashedIntoGroundCheck(GameState* GameStateInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* GameStateInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty(GameState* GameStateInstance);

};
