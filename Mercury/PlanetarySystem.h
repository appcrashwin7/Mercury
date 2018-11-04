#pragma once

#include "Star.h"
#include "Planet.h"

class PlanetarySystem
{
public:
	PlanetarySystem(Star & systemStar);
	~PlanetarySystem();


	Star mainObject;
	std::string name;
private:
	
};