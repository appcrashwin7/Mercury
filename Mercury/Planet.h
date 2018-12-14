#pragma once

#include "CelestialBody.h"

class Planet : public CelestialBody
{
public:
	Planet(double orbit, double radius, double mass);
	~Planet();

private:

};