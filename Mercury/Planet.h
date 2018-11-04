#pragma once

#include "CelestialBody.h"

class Planet : public CelestialBody
{
public:
	Planet(int orbit, int mass, int radius);
	~Planet();

private:

};