#pragma once

#include "PlanetarySystem.h"

class Universe
{
    std::vector<PlanetarySystem> systems;
public:
	Universe() = default;
	Universe(Universe && other) = default;
	~Universe() = default;

	PlanetarySystem & getSystem(size_t index);
	PlanetarySystem* getSystem(const QString& name);
	const PlanetarySystem& getSystem(size_t index) const;
	const PlanetarySystem* getSystem(const QString& name) const;



	void addSystem(const QString & name);
	void addSystem(PlanetarySystem && newSystem);


	const std::vector<PlanetarySystem> & getSystems() const;
	std::vector<PlanetarySystem> & getSystems();


	const PlanetarySystem& getLastSystem() const;
	PlanetarySystem& getLastSystem();
};