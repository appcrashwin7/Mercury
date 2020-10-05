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

	void constructPlayerFactionCols(std::vector<ColonyData> data)
	{
		for (const auto& i : data)
		{
			auto id = std::get<0>(i);
			playerFaction.getColonies().emplace_back(
				Colony(*(dynamic_cast<RockyBody*>(getSystem(id.first).Bodies[id.second].get())),
				std::get<1>(i), std::get<2>(i)));
		}
	}
	void simulate(qint64 days)
	{
		for (size_t i = 0; i < static_cast<size_t>(days); i++)
		{
			for (auto& col : playerFaction.getColonies())
			{
				col.simulate();
			}
		}
	}
};