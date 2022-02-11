#pragma once

#include "gameState.h"
#include "lander.h"



class EnvironmentalForces
{
public:

    void applyGravity();
    void applyIntertia(GameState* GameInstance);
    double totalVelocity();

    static double ddx;
    static double ddy;


private:
    const double GRAVITY = -1.625;
    static double dx;
    static double dy;







};