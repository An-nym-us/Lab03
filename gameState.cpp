/**********************************************************************
*  * 1. Name:
 *      Jonathan Gunderson, Dahal Sulav
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, and writing code-
 *****************************************************************/
 /**********************************************************************

* 
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

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <format>



using namespace std;
static Stars starInstance;


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
    Ground groundInstance = landerInstance->ground;
    UserInterface* userInterfaceInstance = (UserInterface*)p;
    Crash crashInstance;
    Physics physics;



    




    userInterfaceInstance->updateControllerInputs(pUI, landerInstance);      // move the ship around
    userInterfaceInstance->onScreenText(landerInstance, groundInstance);     // put some text on the screen



    starInstance.showStars();     // draw our little star 

    groundInstance.draw(gout);      // draw the ground



    // draw the Physics and its flames
    gout.drawLander(landerInstance->ptLM /*position*/, landerInstance->angle /*angle*/);
    gout.drawLanderFlames(landerInstance->ptLM, landerInstance->angle, /*angle*/
        pUI->isDown(), pUI->isLeft(), pUI->isRight());



    // Create the general physics effect of moon gravity.
    physics.gravity(landerInstance);
    physics.applyThrust(landerInstance, userInterfaceInstance);
    physics.applyIntertia(landerInstance);



}


/*********************************
* Declare static physics variables for simulator
 *********************************/
double Physics::x = 0;
double Physics::y = 0;
double Physics::dx = 0;
double Physics::dy = 0;
double LanderState::fuel = 7777;
/*********************************
* Declare static physics variables for simulator
 *********************************/



 /*********************************
 * Decrement the amount of fuel that
 * is currently in the lander, Only 
 * When the user applys thrust.
  *********************************/
void LanderState::decrementFuel()
{
    fuel--;
}



/*********************************
*
* 
 *********************************/
void UserInterface::updateControllerInputs(const Interface* pUI, LanderState* landerInstance)
{
    if (pUI->isRight())
        landerInstance->angle -= 0.1;
    if (pUI->isLeft())
        landerInstance->angle += 0.1;
    if (pUI->isUp())
        landerInstance->ptLM.addY(-1.0);
    if (pUI->isDown())
        applyThrust = true;
    else
        applyThrust = false;
}


/*********************************
* Create The effect of Gravity
* The lander will be constantly
* Pulled Down.
 *********************************/
void Physics::gravity(LanderState* landerState)
{
    dy += GRAVITY;
}

/*********************************
*
*
 *********************************/
void Physics::applyIntertia(LanderState* landerInstance)
{
    x += dx;
    y += dy;
    landerInstance->ptLM.addY(dy * .03);
    landerInstance->ptLM.addX(dx * .03);
}



/*********************************
*
*
 *********************************/
void Physics::applyThrust(LanderState* landerInstance, UserInterface* userInterfaceInstance)
{
    if (userInterfaceInstance->applyThrust == true)
    {
        dy += (cos(landerInstance->angle) * THRUST / WEIGHT);
        dx += ( - 1 * (sin(landerInstance->angle) * THRUST / WEIGHT));
        landerInstance->decrementFuel();
    }
}


/*********************************
*
*
 *********************************/
double Physics::totalVelocity()
{
    return sqrt(dx * dx + dy * dy) * .1;
}



/*********************************
*
*
 *********************************/
double Crash::altitude(Ground groundInstance, LanderState* landerInstance)
{
    Point landerLocation(landerInstance->ptLM);
    return groundInstance.getElevation(landerLocation);
}

/*********************************
 * Plan on passing reading the values for the
 * onscreen text directly from the lander state.
 *********************************/
void UserInterface::onScreenText(LanderState* landerInstance, Ground groundInstance)
{
    ogstream gout;
    gout.setPosition(Point(30.0, 550.0));

    gout << "Fuel:\t" << landerInstance->fuel << " lbs" << "\n"
        << "Altitude:\t" << Crash().altitude(groundInstance, landerInstance) <<" meters"<<  "\n"
        << "Speed:\t" << Physics().totalVelocity() << showpoint << fixed << setprecision(2) << " m/s";

}


/*********************************
* This will create multiple instances
* of the stars on the screen above 
* the ground.
 *********************************/
void Stars::showStars()
{
   ogstream gout;
    
    vector<Point> points;
    int x[51] = {40,50,60,70,100,20,10,120,150,160,190,200,220,230,240,250,260,270,300,350,360,390,400,410, 450,460,480,500,310,320,480,500,510};
    int y[51] = {400,500,600,410,420,510,520,450,500,600,530,240,560,450,460,490,520,300,330,350,280,290,300,303,403,503,499,599,299,399,320,480,550};
    int z[52] = { 40,50,60,70,100,20,10,120,150,160,190,200,220,230,240,250,20,244,0,10,400,40,60, 45,460,0,50,255,200,200,50,80 };
    
//    Point test; // create random on screen postions for the stars
//    Point test2(100,401);
    for(int i=0; i <31; i++){
        Point test(x[i],y[i]);
        points.push_back(test);
    }
    
    
    for(int i=0; i < points.size(); i++)
    {
        int currentPhase = z[i] + phase;
        gout.drawStar(points[i], currentPhase);
        phase++;
    }
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
