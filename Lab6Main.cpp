/**********************************************************************
*  * 1. Name:
 *      Jonathan Gunderson, Dahal Sulav
 * 2. Assignment Name:
 *      Lab 06: Apollo 11
 *****************************************************************/
 /**********************************************************************
 * GL GameState
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "constellations.h"
#include "star.h"

#include "crash.h"
#include "gameState.h"
#include "lander.h"
#include "environmentalForces.h"
#include "star.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>





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
    playState currentstate = playState(2);

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 

    GameState* GameStateInstance = (GameState*)p;                                                               // Create the Game state class to stay persistance throughout the game session
    Lander& landerInstance = GameStateInstance->getLanderInstance();                                            // Get Lander instance created inside of the GameState class
    Constellations& constellationsInstance = GameStateInstance->getConstellationsInstance();                    // Get Constellations instance created inside of the GameState class
    EnvironmentalForces& environmentalForcesInstance = GameStateInstance->getEnvironmentalForcesInstance();     // Get Environmental Forces instance created inside of the GameState class


    constellationsInstance.show();                              // Draw stars created from inside the constellations class
    GameStateInstance->getGroundInstance().draw(gout);          // Draw ground created from inside the GameState





    SessionState().getCurrentState(currentstate, GameStateInstance);

    if ( currentstate == playState(win))
    {
        GameStateInstance->displayEndGameSession(true);         // Display to user that they WON the game.
    }
    else if (currentstate == playState(lose))
    {
        GameStateInstance->displayEndGameSession(false);        // Display to user that they LOST the game.
    }
    else
    { 
        environmentalForcesInstance.applyGravity();                                         // Apply One Game Tick of Gravity
        environmentalForcesInstance.applyIntertia(landerInstance.getptLMInstance());        // Apply One Game Tick of Intertia
        landerInstance.applyThrustEffect(landerInstance, environmentalForcesInstance);      // Apply One Game Tick ofthrust
        GameStateInstance->getPlayerController(pUI, landerInstance);                        // move the ship around

        // draw lander flames
        gout.drawLanderFlames(landerInstance.getptLMInstance(), landerInstance.getAngle(), /*angle*/
            pUI->isDown(), pUI->isLeft(), pUI->isRight());

        GameStateInstance->onScreenStats();                                                 // put some text on the screen
        gout.drawLander(landerInstance.getptLMInstance() /*position*/, landerInstance.getAngle() /*angle*/);
    }  
}



/*********************************
* iterate through the vector 
* of created star instances
 *********************************/
void Constellations::show()
{
    for (int i = 0; i < constellationsInstance.size(); i++) // Iterate through the stored stars vector.
    { 
        constellationsInstance.at(i).show();    // Display the stars on screen.
    }
}


/*********************************
* Display the star class instance
 *********************************/
void Star::show()
{
    ogstream gout;
    gout.drawStar(location, phase);
    phase++;
}



/*********************************
* Create The effect of Gravity.
* The lander will be constantly
* Pulled Down.
 *********************************/
void EnvironmentalForces::applyGravity()
{
    ddy += GRAVITY;
}



/*********************************
* Apply Intertia effect. The input will be a point in space, 
* taken, altered, and returned to its appropriate new value.
* Time is based on the set dialation which can be calculated
* Based on the current game framerate.
 *********************************/
void EnvironmentalForces::applyIntertia(Point& point)
{
    dx = ddx * TIMEDILATION;
    dy = ddy * TIMEDILATION;

    /*********************************
    *   Apply the kinematic equation of 
    * -->   s = s + vt + 1/2 at^2   <--- 
    * The time is based of the the time dilation game modifier
    *********************************/

    point.setX((point.getX()) + (dx * TIMEDILATION) + (.5 * ddx * (TIMEDILATION * TIMEDILATION)));
    point.setY((point.getY()) + (dy * TIMEDILATION) + (.5 * ddy * (TIMEDILATION * TIMEDILATION)));

}

/*********************************
* Decrement the amount of fuel that
* is currently in the lander, Only
* When the user applys thrust.
 *********************************/
void Lander::decrementFuel()
{
    fuel -= 1;
}


/*********************************
* Set if the player is requesting 
* that thrust be applied to the moon
* lander, by the moon lander.
 *********************************/
void Lander::setThrustActive(bool thrust)
{
    applyThrust = thrust;
}

/*********************************
* Apply thrust to the lander. THis will be appied to the
* current acceleration value. That will need to be 
* follow-up called on by the applyIntertia function.
 *********************************/
void Lander::applyThrustEffect(Lander& landerInstance, EnvironmentalForces& environmentalForcesInstance)
{
    if (landerInstance.isThrustActive() == true)
    {
        environmentalForcesInstance.setDDY(environmentalForcesInstance.getDDY() + (cos(landerInstance.getAngle()) * Lander().THRUST / Lander().WEIGHT));                //acceleration In vertical axis
        environmentalForcesInstance.setDDX(environmentalForcesInstance.getDDX() + (-1 * (sin(landerInstance.getAngle()) * Lander().THRUST / Lander().WEIGHT)));         //acceleration In horizontal axis
        landerInstance.decrementFuel();
    }
}


/*********************************
* Return Current velocity of the tracked
* entitiy that the enviromental forces classes
* was created for.
 *********************************/
double EnvironmentalForces::getTotalVelocity()
{
    return sqrt(dx * dx + dy * dy);
}



/*********************************
* retrieve the players controls, 
* route data to the lander inputs.
 *********************************/
void GameState::getPlayerController(const Interface* pUI, Lander& landerInstance)
{
    if (pUI->isRight())
        landerInstance.setAngle(landerInstance.getAngle() - .1);
    if (pUI->isLeft())
        landerInstance.setAngle(landerInstance.getAngle() + .1);
    if (pUI->isDown())
        landerInstance.setThrustActive(true);
    else
        landerInstance.setThrustActive(false);
}


/*********************************
* Retrun the currnet distance beween the 
* GROUND instnace and the LANDER instance
 *********************************/
double GameState::altitudeToGround()
{
    return this->getGroundInstance().getElevation(landerInstance.getptLMInstance());
}


/*********************************
* Display the end session flavor text.
* Text type is based on a WIN/LOSE condition.
 *********************************/
void GameState::displayEndGameSession(bool endCondition)
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

    gout << "Fuel:\t" << this->getLanderInstance().getFuelStatus() << " lbs" << "\n"
        << "Altitude:\t" << this->altitudeToGround() << " meters" << "\n"
        << "Speed:\t" << this->getEnvironmentalForcesInstance().getTotalVelocity() << showpoint << fixed << setprecision(2) << " m/s";
}





/*********************************
* return the current state of the game session, if the lander 
* is still flying, attempted to land on platform, 
* or crashed into the ground.
 *********************************/
void SessionState::getCurrentState(playState &currentstate, GameState* GameStateInstance)
{
    if ((this->crashedIntoGroundCheck(GameStateInstance)) ||
    this->isFuelEmptyCheck() == true ||
    (this->landedOnPlatformCheck(GameStateInstance) == true // Check if they landed on the platform.
        && 
        this->crashedIntoPlatformCheck(GameStateInstance) == true // ensure player did not hit the plateform at a speed greater 5 m/s
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
* return if the lander has impacted 
* the ground at any point of the gameplay.
 *********************************/
bool SessionState::crashedIntoGroundCheck(GameState* GameStateInstance)
{
    return GameStateInstance->getGroundInstance().hitGround(GameStateInstance->getLanderInstance().getptLMInstance(), Lander().getMoonLanderWidth());
}


/*********************************
* Check if the lander is inside 
* the landing zone.
 *********************************/
bool SessionState::landedOnPlatformCheck(GameState* GameStateInstance)
{ 
    return GameStateInstance->getGroundInstance().onPlatform(GameStateInstance->getLanderInstance().getptLMInstance(), Lander().getMoonLanderWidth());
}


/*********************************
* Check if the lander hit the platform at 
* a velocity greater than 5 m / s. 
* if so, report crash, else landed.
 *********************************/
bool SessionState::crashedIntoPlatformCheck(GameState* GameStateInstance)
{
    if (EnvironmentalForces().getTotalVelocity() > 5.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*********************************
* Retrun current fuel-level of 
* the moon lander.
 *********************************/
bool SessionState::isFuelEmptyCheck()
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
