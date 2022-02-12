/***********************************************************************
 * Header File:
 *    Constellations
 * Author:
 *    Jonathan Gunderson, Dahal Sulav
 * Summary:
 *		A sorted class of multiple instances of the star class
 ************************************************************************/

#pragma once

#include "star.h"
#include <vector>


 /*********************************************
  * Constelation of Stars 
  * Creates the mutiple instances of each star.
  *********************************************/

class Constellations
{
public:
	Constellations() : constellationsInstance(50)			// Create the mutiple instances of each star.
	{	};


	void show();	// Display each star in vector list

private:
	std::vector< Star > constellationsInstance;		// create a stored vector of each star.

};