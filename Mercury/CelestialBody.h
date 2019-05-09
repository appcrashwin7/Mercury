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
	CelestialBody(double radius, double mass, CelestialBodyType type, CelestialBody * parent, Orbit orb, const std::string & name);
	CelestialBody(const CelestialBody & other, CelestialBodyType newType);
	virtual ~CelestialBody();

	std::string name;
	
	const CelestialBodyType type;
	const CelestialBody * const parent;

	const Orbit bodyOrbit;//measured in km
	const double radius;// measured in m
	const double mass;//measured in kg

	const float escapeVelocity; //measured in km/s
	const float surfaceGravity; //in m/s^2
};