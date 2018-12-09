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
	CelestialBody(int orbit, int radius, uint64_t mass);
	~CelestialBody();

	std::string name;
	std::vector<CelestialBody*> Satellites;
	CelestialBody * Parent;
	CelestialBodyType getType() const;

	const int orbitDistance;//measured in km
	const int radius;// measured in km
	const uint64_t mass;//measured in tons

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in g's

private:
};