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
    {
        
    }


    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    Ground ground;



    string onScreenText(); // Centerlize what text to place on screen


};


class Thurst
{

public:
    void sendVectorDirection(LanderState* LanderInstance);
private:

protected:
};

class Crash
{

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


private:

protected:


};