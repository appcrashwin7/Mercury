#pragma once

#include "PlanetarySystem.h"

class Universe
{
public:
	Universe();
	~Universe();

	PlanetarySystem & getSystem(size_t index);
	void addSystem(PlanetarySystem & newSystem);
	void addSystem(PlanetarySystem && newSystem);


	const std::vector<PlanetarySystem> & getSystems() const;
	std::vector<PlanetarySystem> & getSystems();
private:
	std::vector<PlanetarySystem> Systems;
};