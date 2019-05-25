#pragma once

#include "CelestialBody.h"

class Star : public CelestialBody
{
public:
	Star(const CelestialBody & body);
	~Star() override = default;
private:

};