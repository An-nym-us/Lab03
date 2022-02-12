/***********************************************************************
 * Header File:
 *    GameState
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *     This class is designed to hold the states for all on-screen entities 
 *      and their current state within the simulator. All information is funneled 
 *      through the game state class as the director for the current session.
 ************************************************************************/


#pragma once
#include "point.h"
#include "crash.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include "crash.h"
#include "environmentalForces.h"




class GameState 
{
public:
    GameState(const Point& ptUpperRight) :
        ground(ptUpperRight)
    {};


    Ground& const getGroundInstance() { return ground; }
    Lander& const getLanderInstance() { return landerInstance; }
    EnvironmentalForces& const getEnvironmentalForcesInstance() { return environmentalForcesInstance;  }

    void getPlayerController(const Interface* pUI);
    void onScreenStats(); // Centerlize what text to place on screen
    void displayEndGameSession(bool endCondition);
    double altitudeToGround();




private:


    bool endGame = false;
    Point ptUpperRight;   // size of the screen
    Ground ground;
    Lander landerInstance;
    EnvironmentalForces environmentalForcesInstance;


};















