#pragma once

#include "Calc.h"
#include <vector>

enum class CelestialBodyType
{
	Undefided,
	Star,
	Planet,
	GasGiant
};

class CelestialBody
{
protected:
	CelestialBodyType type;


public:
	CelestialBody(int orbit, int radius, int mass);
	~CelestialBody();

	std::string name;
	std::vector<CelestialBody*> Satellites;
	CelestialBodyType getType() const;

	const int orbitDistance;//measured in km
	const int radius;// measured in km
	const int mass;//measured in tons

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in g's

private:
};