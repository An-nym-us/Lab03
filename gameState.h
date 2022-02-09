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

        ptLM(ptUpperRight.getX() - 50, ptUpperRight.getY() - 50),
        ground(ptUpperRight)
    {};



            Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    Ground ground;





    bool endGame = false;

    void endGameSessionInformation(bool endCondition);
    

};



class Lander
{
public:






    void onScreenStats(GameState* gameInstance, Ground groundInstance); // Centerlize what text to place on screen
    void updateControllerInputs(const Interface* pUI, Lander* landerInstance);
    double altitudeToGround(Ground groundInstance, GameState* landerInstance);

    void decrementFuel();
    bool getThrust() { return applyThrust; }


    


    static double fuel;
    static double x;
    static double y;
    static double angle;


    const int MOONLANDERWIDTH = 9.44; // width of the lander in meters
    const double WEIGHT = 15103.00;
    const double THRUST = 45000.00;

private:
    bool applyThrust = false;
};




class Crash
{
public:

    bool crashedIntoGroundCheck(GameState * landerInstance, Ground groundInstance);
    bool landedOnPlatformCheck(GameState* landerInstance, Ground groundInstance);
    bool crashedIntoPlatform();
    bool isFuelEmpty(GameState* GameStateInstance);


private:

};



class Star
{
public:
    void show();

private:
    unsigned char phase;
    Point location;
    ogstream starsOut;

protected:
};





class Thrust
{
public:
    void applyThrust(Lander* landerInstance);
};



class Physics
{
public:
	void gravity();
    void applyIntertia(GameState* GameInstance, Lander* landerInstance);

    double totalVelocity();


    static double dx;
    static double dy;

private:


    // Decalre Normal variables.

    const double GRAVITY = -1.625;




protected:


};