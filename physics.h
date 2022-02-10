#pragma once

#include "gameState.h"
#include "lander.h"



class Physics
{
public:
    void gravity();
    void applyIntertia(GameState* GameInstance, Lander* landerInstance);

    double totalVelocity();


    static double dx;
    static double dy;

private:


    // Declare Normal variables.

    const double GRAVITY = -1.625;







};