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
        ptLM(ptUpperRight.getX() - 50, ptUpperRight.getY() - 50),
        ground(ptUpperRight)
    {    };




    bool endGame = false;


    Ground& const getGroundInstance() { return ground; }
    Point& const getptLMInstance() { return ptLM; }





    void updateControllerInputs(const Interface* pUI, Lander* landerInstance);
    void onScreenStats(); // Centerlize what text to place on screen
    void endGameSessionInformation(bool endCondition);
    double altitudeToGround();

private:




    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    Ground ground;




    


    

};















