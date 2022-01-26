#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"

class LanderState
{
public:
    LanderState(const Point& ptUpperRight) :
        angle(0.0),
        ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
        ground(ptUpperRight)
    {

        phase = random(0, 255);
    }

    // this is just for test purposes.  Don't make member variables public!
    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    unsigned char phase;  // phase of the star's blinking
    Ground ground;
    Point ptStar;



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
//public:
//    Stars(const Point& ptUpperRight) : ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0)
//    {
//        phase = random(0, 255);
//    }
//
//    Point ptStar;
//    unsigned char phase;
//
//private:
//
//protected:
//
};

class Physics
{

public:

	void gravity(LanderState* LanderInstance);


private:

protected:


};