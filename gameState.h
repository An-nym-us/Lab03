#pragma once
#include "point.h"
#include "crash.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"





class GameState 
{
public:
    GameState(const Point& ptUpperRight) :
        ptLM(ptUpperRight.getX() - 50, ptUpperRight.getY() - 50),
        ground(ptUpperRight)
    {    };




    bool endGame = false;


    Ground& getGroundInstance() { return ground; }
    Point& getptLMInstance() { return ptLM; }

    void endGameSessionInformation(bool endCondition);
    void onScreenStats(Ground groundInstance); // Centerlize what text to place on screen

private:

    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    Ground ground;




    

};















