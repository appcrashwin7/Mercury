#pragma once

#include "PlanetarySystem.h"

class Universe
{
public:
	Universe();
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
private:
	std::vector<PlanetarySystem> Systems;
};