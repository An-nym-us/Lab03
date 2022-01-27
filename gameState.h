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
        //ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
        ground(ptUpperRight)
    {
        
        //phase = random(0, 255);  <== Delete this code after showStars system is completed
    }

    // this is just for test purposes.  Don't make member variables public!
    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    //unsigned char phase;  // phase of the star's blinking   <== Delete this code after showStars system is completed
    Ground ground;
    //Point ptStar;   <== Delete this code after showStars system is completed



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