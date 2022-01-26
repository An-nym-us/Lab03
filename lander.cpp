/**********************************************************************
 * GL LanderState
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>


#include <string>
#include <iomanip>
#include <sstream>
#include <format>

using namespace std;

/*************************************************************************
 * LanderState
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
//class LanderState
//{
//public:
//    LanderState(const Point& ptUpperRight) :
//        angle(0.0),
//        ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
//        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
//        ground(ptUpperRight)
//    {
//
//        phase = random(0, 255);
//    }
//
//    // this is just for test purposes.  Don't make member variables public!
//    Point ptLM;           // location of the LM on the screen
//    Point ptUpperRight;   // size of the screen
//    double angle;         // angle the LM is pointing
//    unsigned char phase;  // phase of the star's blinking
//    Ground ground;
//    Point ptStar;
//};

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
    //Stars* starInstance = (Stars*)p;



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
    gout.setPosition(Point(30.0, 550.0));
    //gout << "Demo (" << (int)landerInstance->ptLM.getX() << ", " << (int)landerInstance->ptLM.getY() << ")" << "\n";
    gout << landerInstance->onScreenText();







    // draw our little star
    gout.drawStar(landerInstance->ptStar, landerInstance->phase++);




    // Create the general physics effect of moon gravity.
    Physics().gravity(landerInstance);




}

/*********************************
* 
* 
* 
 *********************************/
void Thurst::sendVectorDirection(LanderState* Instance)
{
    
    double dy = 0;
    double dx = 0;
    dx = sin(Instance->angle) * -2;
    dy = cos(Instance->angle) * 2;
    cout << "dy = " << dy << "   dx = " << dx << endl;
    Instance->ptLM.addY(dy);
    Instance->ptLM.addX(dx);


}



/*********************************
*
*
*
 *********************************/
string LanderState::onScreenText()
{
    double fuel = 777777.00;
    double altitude = 777.00;
    double speed = 7.00;

    
    string outstring =
        "Fuel:\t" + to_string(fuel) + "\n" 
        + "Altitude:\t" + to_string(altitude) + "\n"
        + "Speed:\t" + to_string(speed)

        
        ;




    return outstring;
}




/*********************************
* Create The effect of Gravity 
* The lander will be constantly 
* Pulled Down.
 *********************************/
void Physics::gravity(LanderState* demo)
{
    demo->ptLM.addY(-0.5);
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
