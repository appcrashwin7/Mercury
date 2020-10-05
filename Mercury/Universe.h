#pragma once

#include "PlanetarySystem.h"
#include "Faction.h"

class Universe
{
    std::vector<PlanetarySystem> systems;
	Faction playerFaction;
public:
	Universe() = default;
	Universe(Universe && other) = default;
	~Universe() = default;

	PlanetarySystem & getSystem(size_t index);
	PlanetarySystem* getSystem(const QString& name);
	const PlanetarySystem& getSystem(size_t index) const;
	const PlanetarySystem* getSystem(const QString& name) const;


	Faction& getPlayerFaction()
	{
		return playerFaction;
	}
	const Faction & getPlayerFaction() const
	{
		return playerFaction;
	}


	void addSystem(const QString & name);
	void addSystem(PlanetarySystem && newSystem);


	const std::vector<PlanetarySystem> & getSystems() const;
	std::vector<PlanetarySystem> & getSystems();


	const PlanetarySystem& getLastSystem() const;
	PlanetarySystem& getLastSystem();
};