#pragma once

#include "Star.h"
#include "Planet.h"

class PlanetarySystem
{
public:
	PlanetarySystem(const std::string & sysName);
	~PlanetarySystem();


	std::string name;
	std::vector<CelestialBody*> Bodies;
private:
	
};