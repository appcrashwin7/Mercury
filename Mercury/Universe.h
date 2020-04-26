#pragma once

#include "PlanetarySystem.h"

class Universe
{
    std::vector<PlanetarySystem> Systems;
public:
	Universe() = default;
	Universe(Universe && other) = default;
	~Universe() = default;

	PlanetarySystem & getSystem(size_t index);


	void addSystem(const QString & name);
	void addSystem(PlanetarySystem && newSystem);


	const std::vector<PlanetarySystem> & getSystems() const;
	std::vector<PlanetarySystem> & getSystems();


	const PlanetarySystem & getLastSystem() const
	{
		return Systems.back();
	}
	PlanetarySystem & getLastSystem()
	{
		return Systems.back();
	}	
};