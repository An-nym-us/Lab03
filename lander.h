#pragma once

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "gameState.h"





class Lander
{
public:
    void onScreenStats(GameState* gameInstance, Ground groundInstance); // Centerlize what text to place on screen
    void updateControllerInputs(const Interface* pUI, Lander* landerInstance);


    void decrementFuel();

    bool getThrust() { return applyThrust; }
    void setThrust(bool thrust);
    void getThrust(Lander* landerInstance);




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