/***********************************************************************
 * Header File:
 *    class SessionState

 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *
 ************************************************************************/


#pragma once
#include "gameState.h"

enum playState { win, lose, resume };

class SessionState
{
public:
    void sessionState(playState &currentstate, GameState* GameStateInstance) ;

private:
    bool crashedIntoGroundCheck(GameState* GameStateInstance);
    bool landedOnPlatformCheck(GameState* GameStateInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty();
};


