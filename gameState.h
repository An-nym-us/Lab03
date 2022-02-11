#pragma once
#include "point.h"
#include "crash.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include "crash.h"





class GameState 
{
public:
    GameState(const Point& ptUpperRight) :
        ground(ptUpperRight)
    {    };




    bool endGame = false;

    Ground& const getGroundInstance() { return ground; }
    void updateControllerInputs(const Interface* pUI);
    void onScreenStats(); // Centerlize what text to place on screen
    void endGameSessionInformation(bool endCondition);
    double altitudeToGround();




private:



    Point ptUpperRight;   // size of the screen
    Ground ground;




    


    

};















