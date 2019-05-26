#pragma once

#include "Star.h"
#include "Planet.h"

class PlanetarySystem
{
public:
	PlanetarySystem(const std::string & sysName);
	PlanetarySystem(const PlanetarySystem & other) = delete;
	PlanetarySystem(PlanetarySystem && system) = default;
	~PlanetarySystem() = default;


	std::string name;
	std::vector<CelestialBodyPtr> Bodies;
private:
	
};