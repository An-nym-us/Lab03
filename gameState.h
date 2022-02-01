#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"

#include <iostream>

class LanderState
{
public:
    LanderState(const Point& ptUpperRight) :
        angle(0.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
        ground(ptUpperRight)
    {};

    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    Ground ground;



    //DEBUG
    double landerDX = 0; // lander stating state
    double landerDY = 0; // lander stating state
    double fuel = 7777;
    double speed = 77;
    double altitude = 777;



    void onScreenText(LanderState* landerInstance); // Centerlize what text to place on screen


};


class Thrust
{
public:
    void sendVectorDirection(LanderState* LanderInstance);
    void updateControllerInputs(const Interface* pUI, LanderState* LanderInstance);

private:

protected:
};



class Crash
{
public:
    bool isInGround(LanderState * landerInstance);

private:

protected:
};



class Stars
{
public:
    void showStars();

private:

protected:

};




class Physics
{

public:
	void gravity(LanderState* LanderInstance);
    void Momentum(LanderState* LanderInstance);


private:

    short ax = 0;
    short dx = 0;
    double time = 0;



protected:


};