#pragma once

#include "Calc.h"

class Orbit 
{
public:
	const Length apoapsis = Length(units::si::meter * 0);
	const Length periapsis = Length(units::si::meter * 0);

	const float eccentricity = 0.0f;

	const bool isZero = true;

	Orbit() = default;
	Orbit(Length apo, Length per)
		:apoapsis(apo), periapsis(per),
		eccentricity(Calc::getEccentric(apo, per)), isZero(false)
	{}
	Orbit(Length radius)
		:apoapsis(radius), periapsis(radius), isZero(false)
	{}
	Orbit(const Orbit & other) = default;
	~Orbit() = default;
};
