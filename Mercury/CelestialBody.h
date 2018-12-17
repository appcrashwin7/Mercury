#pragma once

#include "Orbit.h"
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
public:
	CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * parent, Orbit orb);
	CelestialBody(CelestialBody & other, CelestialBodyType newType);
	~CelestialBody();

	std::string name;
	
	const CelestialBodyType type;
	const CelestialBody * const parent;

	const Orbit bodyOrbit;//measured in km
	const double radius;// measured in m
	const double mass;//measured in kg

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in m/s^2

	const std::vector<CelestialBody*> & getSatellites() const;
	std::vector<CelestialBody*> & getSatellites();

private:
	std::vector<CelestialBody*> Satellites;

};