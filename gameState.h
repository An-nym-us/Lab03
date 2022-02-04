#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include <vector>
#include <random>

#include <iostream>

class GameState 
{
public:
    GameState(const Point& ptUpperRight) : 
        angle(0.0),
        ptLM(ptUpperRight.getX() - 50, ptUpperRight.getY() - 50),
        ground(ptUpperRight)
    {};

    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    Ground ground;



    const int MOONLANDERWIDTH = 9.44; // width of the lander in meters
    double angle;         // angle the LM is pointing
    static double fuel;
    bool endGame = false;


    void decrementFuel();
};



class UserInterface
{
public:
    bool applyThrust = false;

    void onScreenText(GameState* landerInstance, Ground groundInstance); // Centerlize what text to place on screen
    void updateControllerInputs(const Interface* pUI, GameState* LanderInstance);
    
private:

protected:

};




class Crash
{
public:
    bool crashedIntoGroundCheck(GameState * landerInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* landerInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    double altitude(Ground groundInstance, GameState* landerInstance);

private:

protected:
};



class Stars
{
public:
    void showStars();

private:
    unsigned char phase;
    Point location;
    ogstream starsOut;

protected:

};



class Physics
{
public:
	void gravity(GameState* LanderInstance);
    void applyIntertia(GameState* LanderInstance);
    void applyThrust(GameState* LanderInstance, UserInterface* userInterfaceInstance);
    double totalVelocity();


private:

    // Declare static variables.
    static double x;
    static double y;
    static double dx;
    static double dy;


    // Decalre Normal variables.
    double angle = 0;
    const double WEIGHT = 15103.00;
    const double GRAVITY = -1.625;
    const double THRUST = 45000.00;
    double time = 0;



protected:


};