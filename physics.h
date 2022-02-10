#pragma once

#include "gameState.h"
#include "lander.h"



class Physics
{
public:

    void gravity();
    void applyIntertia(GameState* GameInstance);
    double totalVelocity();


    static double dx;
    static double dy;

private:
    const double GRAVITY = -1.625;







};