/***********************************************************************
 * Header File:
 *    GameState
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *  This class is designed to hold the states for all on-screen entities 
 *      and their current state within the simulator. All instances are 
 *      created when this class is initiated and those instances will not be 
 *      destroyed until THIS created class (the gamestate) is destroyed.
 *  Remember that this is the director for the simulator, if the 
 *      director dies, the show dies/ends.   
 ************************************************************************/


#pragma once
#include "point.h"
#include "crash.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include "crash.h"
#include "star.h"
#include "environmentalForces.h"


 /***********************************************************
  * Class Game State 
  ***********************************************************/

class GameState 
{
public:
    // Constructor 
    GameState(const Point& ptUpperRight) :
        ground(ptUpperRight)
    {};

    // Instances of the class 
    Ground& const getGroundInstance() { return ground; }            // Return the current instance of the created GROUND class created in THIS GameState Class
    Lander& const getLanderInstance() { return landerInstance; }    // Return the current instance of the created LANDER class  created in THIS GameState Class
    Constellations& const getConstellationsInstance() { return constellationsInstance;  }               // Return the current instance of the created CONSTELLATIONS class  created in THIS GameState Class
    EnvironmentalForces& const getEnvironmentalForcesInstance() { return environmentalForcesInstance;}  // Return the current instance of the created ENVIROMENTALFORCES class created in THIS GameState Class

    // Methods 
    void getPlayerController(const Interface* pUI, Lander& landerInstance);                 // retrieve the players controls, route data to the lander controls
    void onScreenStats();                                           // Centerlize what text to place on screen
    void displayEndGameSession(bool endCondition);                  // Display the end game result, 
    double altitudeToGround();                                      // Display the currnet distance beween the GROUND instance and the LANDER instance




private:


    bool endGame = false;

    /* Class Generated Instances For Session */
    Point ptUpperRight;                                     // Size of the screen.
    Ground ground;                                          // Create ground image.
    Lander landerInstance;                                  // Create stored instance of the lander state.
    EnvironmentalForces environmentalForcesInstance;        // Create stored instance of the envoirmental physiscs

    Constellations constellationsInstance;
};















