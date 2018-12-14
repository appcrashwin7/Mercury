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
	CelestialBody(double orbit, double radius, double mass);
	~CelestialBody();

	std::string name;
	std::vector<CelestialBody*> Satellites;
	CelestialBody * Parent;
	CelestialBodyType getType() const;

	const double orbitDistance;//measured in km
	const double radius;// measured in km
	const double mass;//measured in kg

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in g's

private:
};