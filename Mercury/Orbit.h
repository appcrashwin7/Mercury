#pragma once

#include "Calc.h"

class Orbit 
{
public:
	// in meters
	const double apoapsis = 0.0;
	const double periapsis = 0.0;

	const float eccentricity = 0.0f;

	const bool isZero = true;

	Orbit() = default;
	Orbit(double apo, double per)
		:apoapsis(apo), periapsis(per),
		eccentricity(Calc::getEccentric(apo, per)), isZero(false)
	{}
	Orbit(double radius)
		:apoapsis(radius), periapsis(radius), isZero(false)
	{}
	Orbit(const Orbit & other)
		:apoapsis(other.apoapsis), periapsis(other.periapsis),
		eccentricity(other.eccentricity), isZero(other.isZero)
	{}
	~Orbit() = default;
};
