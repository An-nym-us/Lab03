#pragma once

#include "gameState.h"

enum playState { win, lose, resume };

class Crash
{
public:
    void landerCrashed(playState &currentstate, GameState* GameStateInstance) ;

private:
    bool crashedIntoGroundCheck(GameState* GameStateInstance);
    bool landedOnPlatformCheck(GameState* GameStateInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty();
};


