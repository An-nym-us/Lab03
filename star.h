/***********************************************************************
 * Header File:
 *    Star
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *      An instance of each individual star
 ************************************************************************/
#pragma once
#include <random>
#include <vector>


 /*********************************************
  * Star
  * A single Star 
  *********************************************/

class Star
{
public:
    // Constructor 
    Star() : location((rand() % 500 + 50), (rand() % 500 + 30))             // set a random location for the star on the screeen.
    {
        phase = random(0, 255);         // set a default random starting brightness.
    };


    void show();                // Display the star at its location and phase on screen.
private:
    unsigned char phase;        // Init Phase variable.
    Point location;             // Create on-screen location.



};