/**********************************************************************
 * GL LanderState
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "gameState.h"
#include <iostream>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>


#include <string>
#include <iomanip>
#include <sstream>
#include <format>

using namespace std;



/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    
    
    ogstream gout;

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    LanderState* landerInstance = (LanderState*)p;
    Stars starInstance;



    // move the ship around
    if (pUI->isRight())
        landerInstance->angle -= 0.1;
    if (pUI->isLeft())
        landerInstance->angle += 0.1;
    if (pUI->isUp())
        landerInstance->ptLM.addY(-1.0);
    if (pUI->isDown())
        Thurst().sendVectorDirection(landerInstance);


    // draw the ground
    landerInstance->ground.draw(gout);

    // draw the Physics and its flames
    gout.drawLander(landerInstance->ptLM /*position*/, landerInstance->angle /*angle*/);
    gout.drawLanderFlames(landerInstance->ptLM, landerInstance->angle, /*angle*/
        pUI->isDown(), pUI->isLeft(), pUI->isRight());





    // put some text on the screen

    landerInstance->onScreenText();


    // draw our little star 
    // TODO
   
    starInstance.showStars();



    // Create the general physics effect of moon gravity.
    Physics().gravity(landerInstance);




}

/*********************************
* Apply trust to lander depending
* on its current orentation.
 *********************************/
void Thurst::sendVectorDirection(LanderState* Instance)
{
    
    Instance->landerDX = sin(Instance->angle) * -2;
    Instance->landerDY = cos(Instance->angle) * 2;


    cout << "dy = " << Instance->landerDY << "   dx = " << Instance->landerDX << endl; // Debugg

    Instance->ptLM.addY(Instance->landerDY);
    Instance->ptLM.addX(Instance->landerDX);


}



/*********************************
*
*
 *********************************/
void LanderState::onScreenText()
{
    ogstream gout;
    gout.setPosition(Point(30.0, 550.0));


    static double fuel = 777777.00;
    double altitude = 777.00;
    double speed = 7.00;

    // debug fuel system
    fuel--;

        gout << "Fuel:\t" << fuel << "\n" 
        << "Altitude:\t" << altitude << "\n"
        << "Speed:\t" << speed << showpoint << fixed << setprecision(2);


}


/*********************************
* This will create multiple instances
* of the stars on the screen above 
* the ground.
 *********************************/
void Stars::showStars()
{
    ogstream gout;

    Point test(random(1,  600), random(400, 600)); // create random on screen postions for the stars
    gout.drawStar(test, random(1, 255));  // show the stars at different intensity values
    
}




/*********************************
* Create The effect of Gravity 
* The lander will be constantly 
* Pulled Down.
 *********************************/
void Physics::gravity(LanderState* landerState)
{
    landerState->ptLM.addY(-0.5);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my LanderState type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Initialize OpenGL
    Point ptUpperRight(600.0, 600.0);
    Interface ui(0, NULL,
        "Open GL Demo",
        ptUpperRight);

    // Initialize the game class
    LanderState demo(ptUpperRight);


    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}
