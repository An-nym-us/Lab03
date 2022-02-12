/***********************************************************************
 * Header File:
 *    class SessionState
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *      Check the current state of the game session. The current 
 *      session will be reported as an enum. This will check many aspects 
 *      of the game to report the correct state of the game 
 *      to the callback function.
 ************************************************************************/
#pragma once
#include "gameState.h"


enum playState { win, lose, resume };   // enum of thre current play state of the game. Used to designate if the game is done.

class SessionState
{
public:

    /* return the current state of the game session, if the lander is still flying, attempted to land on platform, or crashed into the ground */
    void getCurrentState(playState &currentstate, GameState* GameStateInstance);   

private:

    bool crashedIntoGroundCheck(GameState* GameStateInstance);      // Check if the lander has impacted the ground at any point of the gameplay.
    bool landedOnPlatformCheck(GameState* GameStateInstance);       // Check if the lander is inside the landing zone.
    bool crashedIntoPlatformCheck(GameState* GameStateInstance);    // Check if the lander hit the platform at a velocity greater than 5 m/s. if so, report crash, else landed
    bool isFuelEmptyCheck();                                        // Check current fuel-level of the moon lander
};


