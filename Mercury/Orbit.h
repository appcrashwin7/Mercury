#pragma once

#include "Calc.h"

class Orbit 
{
public:
	const double apoapsis;
	const double periapsis;

	const float eccentricity;

	const bool isZero;

	Orbit()
		:apoapsis(0.0), periapsis(0),
		eccentricity(0), isZero(true)
	{}
	Orbit(double apo, double per)
		:apoapsis(apo), periapsis(per),
		eccentricity(Calc::getEccentric(apo, per)),
		isZero(false)
	{

	}
	Orbit(double radius)
		:apoapsis(radius), periapsis(radius),
		eccentricity(0), isZero(false)
	{}
	Orbit(const Orbit & other)
		:apoapsis(other.apoapsis), periapsis(other.periapsis),
		eccentricity(other.eccentricity), isZero(other.isZero)
	{}
	~Orbit() = default;
};
