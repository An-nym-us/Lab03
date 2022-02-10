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
    //GameStateInstance->getLanderInstance

    Lander* landerInstance = (Lander*)p;
    Crash crashInstance;
    



    GameStateInstance->getGroundInstance().draw(gout);   // draw our little star 
    starInstance.show();      


    GameStateInstance->onScreenStats(GameStateInstance->getGroundInstance());     // put some text on the screen
    gout.drawLander(GameStateInstance->getptLMInstance() /*position*/, landerInstance->angle /*angle*/);


    //if (Integrate endgame function into a single function )
    //    {

    //    }
    //else
    //{ 
    //}




    // END GAME CHECK   
    if ((crashInstance.crashedIntoGroundCheck(GameStateInstance, GameStateInstance->getGroundInstance())) ||
        crashInstance.isFuelEmpty(GameStateInstance) == true ||
        (crashInstance.landedOnPlatformCheck(GameStateInstance, GameStateInstance->getGroundInstance()) == true // Check if they landed on the platform.
            && 
            crashInstance.crashedIntoPlatform() == true // ensure player did not hit the plateform at a speed greater 5 m/s
        ))
    {
        GameStateInstance->endGameSessionInformation(false);  // Display to user that they LOST the game.
    }
    else if (crashInstance.landedOnPlatformCheck(GameStateInstance, GameStateInstance->getGroundInstance()))
    {
        GameStateInstance->endGameSessionInformation(true);// Display to user that they WON the game.
    }
    else
    {
        // Create the general physics effect of moon gravity.
        Physics().gravity();
        Physics().applyIntertia(GameStateInstance);
        Lander().applyThrustEffect(landerInstance);
        landerInstance->updateControllerInputs(pUI, landerInstance);      // move the ship around



        // draw lander flames
        gout.drawLanderFlames(GameStateInstance->getptLMInstance(), landerInstance->angle, /*angle*/
            pUI->isDown(), pUI->isLeft(), pUI->isRight());
    }
    
}


/*********************************
* Declare static physics variables for simulator
 *********************************/
double Lander::x = 550;
double Lander::y = 550;
double Lander::angle = 0;
double Lander::fuel = 7777;
double Physics::dx = 0;
double Physics::dy = 0;

/*********************************
* Declare static physics variables for simulator
 *********************************/



 /*********************************
 * Decrement the amount of fuel that
 * is currently in the lander, Only 
 * When the user applys thrust.
  *********************************/
void Lander::decrementFuel()
{
    this->fuel--;
}

void Lander::setThrust(bool thrust)
{
    applyThrust = thrust;
}

/*********************************
*
* 
 *********************************/
void Lander::updateControllerInputs(const Interface* pUI, Lander* landerInstance)
{
    if (pUI->isRight())
        landerInstance->angle -= 0.1;
    if (pUI->isLeft())
        landerInstance->angle += 0.1;
    //if (pUI->isUp())
        //GameStateInstance->ptLM.addY(-1.0);
    if (pUI->isDown())
        landerInstance->setThrust(true);
    else
        landerInstance->setThrust(false);

}


/*********************************
* Create The effect of Gravity
* The lander will be constantly
* Pulled Down.
 *********************************/
void Physics::gravity()
{
    dy += GRAVITY *.1;
}

/*********************************
*
*
 *********************************/
void Physics::applyIntertia(GameState* GameStateInstance)
{
    //landerInstance->x += dx * .1;
    //landerInstance->y += dy *.1;
    //GameStateInstance->getptLMInstance().setX(landerInstance->x);
    //GameStateInstance->getptLMInstance().setY(landerInstance->y);


        //  
    // replace  "s = s + v"  integrate "s = s + vt + 1/2 at^2"


    GameStateInstance->getptLMInstance().setX(( GameStateInstance->getptLMInstance().getX() + dx));
    GameStateInstance->getptLMInstance().setY(( GameStateInstance->getptLMInstance().getY() + dy));





}



/*********************************
*
*
 *********************************/
void Lander::applyThrustEffect(Lander* landerInstance)
{
    if (landerInstance->getThrust() == true)
    {
        Physics().dy += (cos(landerInstance->angle) * Lander().THRUST / Lander().WEIGHT) *.1;

        Physics().dx += ( - 1 * (sin(landerInstance->angle) * Lander().THRUST / Lander().WEIGHT)) *.1;

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
double Crash::altitudeToGround(Ground groundInstance, GameState* GameStateInstance)
{
    Point landerLocation(GameStateInstance->getptLMInstance());
    return groundInstance.getElevation(landerLocation);
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
void GameState::onScreenStats(Ground groundInstance)
{
    ogstream gout;
    gout.setPosition(Point(30.0, 550.0));

    gout << "Fuel:\t" << Lander().fuel << " lbs" << "\n"
        << "Altitude:\t" << Crash().altitudeToGround(groundInstance, this) << " meters" << "\n"
        << "Speed:\t" << Physics().totalVelocity() << showpoint << fixed << setprecision(2) << " m/s";
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
bool Crash::crashedIntoGroundCheck(GameState* GameStateInstance, Ground groundInstance)
{
    return groundInstance.hitGround(GameStateInstance->getptLMInstance(), Lander().MOONLANDERWIDTH);
}


/*********************************
*
*
 *********************************/
bool Crash::landedOnPlatformCheck(GameState* GameStateInstance, Ground groundInstance)
{ 
    return groundInstance.onPlatform(GameStateInstance->getptLMInstance(), Lander().MOONLANDERWIDTH);
}


/*********************************
*
*
 *********************************/
bool Crash::crashedIntoPlatform()
{
    if (Physics().totalVelocity() > 5.0)
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
bool Crash::isFuelEmpty(GameState* GameStateInstance)
{
    if (Lander().fuel <= 0.0)
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