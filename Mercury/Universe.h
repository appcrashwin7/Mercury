#pragma once

#include "PlanetarySystem.h"

class Universe
{
public:
	Universe();
	~Universe();

	PlanetarySystem & getSystem(size_t index);
	void addSystem(PlanetarySystem & newSystem);
private:
	std::vector<PlanetarySystem> Systems;
};