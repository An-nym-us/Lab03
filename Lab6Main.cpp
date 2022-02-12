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
 * GL GameState
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"


#include "crash.h"
#include "gameState.h"
#include "lander.h"
#include "physics.h"
#include "star.h"




#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <format>



using namespace std;
static Star starInstance;
static Lander landerInstance;



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
    GameState* GameStateInstance = (GameState*)p;
    playState currentstate = playState(2);




    starInstance.show();
    GameStateInstance->getGroundInstance().draw(gout);   // draw our little star 
    




    Crash().landerCrashed(currentstate, GameStateInstance);

    if ( currentstate == playState(win))
    {
        GameStateInstance->endGameSessionInformation(true);// Display to user that they WON the game.
    }
    else if (currentstate == playState(lose))
    {
        GameStateInstance->endGameSessionInformation(false);
    }
    else
    { 
        EnvironmentalForces().applyGravity();
        EnvironmentalForces().applyIntertia(GameStateInstance);
        landerInstance.applyThrustEffect();
        GameStateInstance->updateControllerInputs(pUI);      // move the ship around

        // draw lander flames
        gout.drawLanderFlames(landerInstance.getptLMInstance(), landerInstance.getAngle(), /*angle*/
            pUI->isDown(), pUI->isLeft(), pUI->isRight());

        GameStateInstance->onScreenStats();     // put some text on the screen
        gout.drawLander(landerInstance.getptLMInstance() /*position*/, landerInstance.getAngle() /*angle*/);
    }





    
}


/*********************************
* 
 *********************************/
double EnvironmentalForces::dx = 0;
double EnvironmentalForces::dy = 0;
double EnvironmentalForces::ddx = 0;
double EnvironmentalForces::ddy = 0;

/*********************************
* 
 *********************************/



 /*********************************
 * Decrement the amount of fuel that
 * is currently in the lander, Only 
 * When the user applys thrust.
  *********************************/
void Lander::decrementFuel()
{
    fuel -= 1;
}

void Lander::setThrust(bool thrust)
{
    applyThrust = thrust;
}

/*********************************
*
* 
 *********************************/
void GameState::updateControllerInputs(const Interface* pUI)
{
    if (pUI->isRight())
        landerInstance.setAngle(landerInstance.getAngle() - .1);
    if (pUI->isLeft())
        landerInstance.setAngle(landerInstance.getAngle() + .1);
    if (pUI->isDown())
        landerInstance.setThrust(true);
    else
        landerInstance.setThrust(false);

}


/*********************************
* Create The effect of Gravity
* The lander will be constantly
* Pulled Down.
 *********************************/
void EnvironmentalForces::applyGravity()
{
    ddy += GRAVITY;
}

/*********************************
*
*
 *********************************/
void EnvironmentalForces::applyIntertia(GameState* GameStateInstance)
{


    dx = ddx * .1;
    dy = ddy * .1;

    double storestateX = (landerInstance.getptLMInstance().getX());
    double storestateY = (landerInstance.getptLMInstance().getY());

    storestateX = storestateX + (dx * .1) + (.5 * ddx * (.1 * .1));
    storestateY = storestateY + (dy * .1) + (.5 * ddy * (.1 * .1));


    landerInstance.getptLMInstance().setX(storestateX);
    landerInstance.getptLMInstance().setY(storestateY);





}



/*********************************
*
*
 *********************************/
void Lander::applyThrustEffect()
{
    if (landerInstance.isThrust() == true)
    {
        EnvironmentalForces().ddy += (cos(landerInstance.getAngle()) * Lander().THRUST / Lander().WEIGHT); //acceleration
        EnvironmentalForces().ddx += ( - 1 * (sin(landerInstance.getAngle()) * Lander().THRUST / Lander().WEIGHT));

        landerInstance.decrementFuel();
    }
}


/*********************************
*
*
 *********************************/
double EnvironmentalForces::totalVelocity()
{
    return sqrt(dx * dx + dy * dy);
}





/*********************************
*
*
 *********************************/
double GameState::altitudeToGround()
{
    return this->getGroundInstance().getElevation(landerInstance.getptLMInstance());
}





/*********************************
*
*
 *********************************/
void GameState::endGameSessionInformation(bool endCondition)
{
    ogstream endGameSessionInformationOut;
    endGameSessionInformationOut.setPosition(Point(250, 400.0));
    if (endCondition == true)
    {
        endGameSessionInformationOut << "YOU WIN  :D";
    }
    else
    {
        endGameSessionInformationOut << "YOU LOSE  :(";
    }
}




/*********************************
 * Plan on passing reading the values for the
 * onscreen text directly from the lander state.
 *********************************/
void GameState::onScreenStats()
{
    ogstream gout;
    gout.setPosition(Point(30.0, 550.0));

    gout << "Fuel:\t" << landerInstance.getFuelStatus() << " lbs" << "\n"
        << "Altitude:\t" << this->altitudeToGround() << " meters" << "\n"
        << "Speed:\t" << EnvironmentalForces().totalVelocity() << showpoint << fixed << setprecision(2) << " m/s";
}


/*********************************
* This will create multiple instances
* of the stars on the screen above 
* the ground.
 *********************************/
void Star::show()
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
*
*
 *********************************/
void Crash::landerCrashed(playState &currentstate, GameState* GameStateInstance)
{
    if ((this->crashedIntoGroundCheck(GameStateInstance)) ||
    this->isFuelEmpty() == true ||
    (this->landedOnPlatformCheck(GameStateInstance) == true // Check if they landed on the platform.
        && 
        this->crashedIntoPlatform() == true // ensure player did not hit the plateform at a speed greater 5 m/s
    ))
    {
        currentstate = playState(1);
    }
    else if (this->landedOnPlatformCheck(GameStateInstance))
    {
        currentstate = playState(0);
    }
    else
    {
        currentstate = playState(2);
    }
}

/*********************************
*
*
 *********************************/
bool Crash::crashedIntoGroundCheck(GameState* GameStateInstance)
{
    return GameStateInstance->getGroundInstance().hitGround(landerInstance.getptLMInstance(), Lander().getMoonLanderWidth());
}


/*********************************
*
*
 *********************************/
bool Crash::landedOnPlatformCheck(GameState* GameStateInstance)
{ 
    return GameStateInstance->getGroundInstance().onPlatform(landerInstance.getptLMInstance(), Lander().getMoonLanderWidth());
}


/*********************************
*
*
 *********************************/
bool Crash::crashedIntoPlatform()
{
    if (EnvironmentalForces().totalVelocity() > 5.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




/*********************************
*
*
 *********************************/
bool Crash::isFuelEmpty()
{
    if (Lander().getFuelStatus() <= 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }

}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my GameState type and call the display engine.
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
        "Open GL",
        ptUpperRight);

    // Initialize the game class
    GameState demo(ptUpperRight);



    // set everything into action
    ui.run(callBack, &demo);

   

    return 0;
}
