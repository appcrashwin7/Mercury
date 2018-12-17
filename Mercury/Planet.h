#pragma once

#include "CelestialBody.h"

class Planet : public CelestialBody
{
public:
	Planet(double radius, double mass, CelestialBody * parent, Orbit orbit);
	Planet(CelestialBody & body);
	~Planet();

private:

};