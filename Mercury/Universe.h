#pragma once

#include "PlanetarySystem.h"

class Universe
{
public:
	Universe();
	Universe(Universe && other) = default;
	~Universe() = default;

	PlanetarySystem & getSystem(size_t index);
	void addSystem(const std::string & name);
	void addSystem(PlanetarySystem && newSystem);


	const std::vector<PlanetarySystem> & getSystems() const;
	std::vector<PlanetarySystem> & getSystems();
private:
	std::vector<PlanetarySystem> Systems;
};