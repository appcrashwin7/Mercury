#pragma once

#include "CelestialBody.h"

class Planet : public CelestialBody
{
public:
	Planet(int orbit, uint64_t mass, int radius);
	~Planet();

private:

};