#pragma once

#include "ResourceDeposit.h"
#include "Commodities.h"

static constexpr uint64_t MINE_BASE_OUTPUT = 10;
static constexpr uint64_t HOUSING_POPULATION_SUPPORT = 1000;
static constexpr uint64_t TERRAN_BASE_INFRASTRUCTURE_SUPPORT = 10;

class IndustryBuilding
{
public:
	IndustryBuilding() = delete;
	IndustryBuilding(const IndustryBuilding & other)
		:baseOutput(other.baseOutput), baseInput(other.baseInput), energyDrain(other.energyDrain), 
		baseCost(other.baseCost), name(other.name)
	{
	};
	IndustryBuilding(const std::string & name, const StockT & output, const StockT & input, int64_t drain, const StockT & cost)
		:baseOutput(output), baseInput(input), energyDrain(drain), baseCost(cost), name(name)
	{};
	~IndustryBuilding() = default;

	const std::string name;
	const StockT baseOutput;
	const StockT baseInput;
	//In megawatts, value lower than 0 mean that building is actually producing energy
	const int64_t energyDrain;

	const StockT baseCost;

	static std::vector<IndustryBuilding> getDefaultBuildings()
	{
		Commodities commd;
		return std::vector<IndustryBuilding>({
			IndustryBuilding("Infrastructure", StockT(), StockT(), 0, StockT({StockUnit(commd["Steel"], 2)})),
			IndustryBuilding("Mine", StockT(), StockT(), 1, StockT({StockUnit(commd["Industrial parts"], 5), StockUnit(commd["Steel"], 1)})),
			IndustryBuilding("Housing", StockT(), StockT(), 1, StockT({StockUnit(commd["Steel"], 10)})),
			IndustryBuilding("Steel Forge", StockT({StockUnit(commd["Steel"], 10)}), StockT({StockUnit(commd["Iron"], 9), StockUnit(commd["Carbon"], 1)}),
			10, StockT({StockUnit(commd["Industrial parts"], 40), StockUnit(commd["Steel"], 10)})),

			IndustryBuilding("Stainless steel Forge", StockT({StockUnit(commd["Stainless steel"], 10)}),
			StockT({StockUnit(commd["Iron"], 10), StockUnit(commd["Carbon"], 1)}), 45, StockT({StockUnit(commd["Steel"], 10), StockUnit(commd["Industrial parts"], 50)})),

			IndustryBuilding("Duraluminium Forge", StockT({StockUnit(commd["Duraluminium"], 10)}), StockT({StockUnit(commd["Aluminum"], 9), StockUnit(commd["Copper"], 1)}),
			50, StockT({StockUnit(commd["Industrial parts"], 40), StockUnit(commd["Steel"], 10)})),

			IndustryBuilding("Industrial Parts Factory", StockT({StockUnit(commd["Industrial parts"], 100)}),
			StockT({StockUnit(commd["Steel"], 20), StockUnit(commd["Copper"], 5), StockUnit(commd["Stainless steel"], 10), StockUnit(commd["Aluminum"], 5), StockUnit(commd["Lead"], 10)}), 50,
			StockT({StockUnit(commd["Steel"], 50), StockUnit(commd["Lead"], 5)})),

			IndustryBuilding("Rocket Parts Factory", StockT({StockUnit(commd["Rocket parts"], 50)}),
			StockT({StockUnit(commd["Titanium"], 10), StockUnit(commd["Duraluminium"], 5), StockUnit(commd["Aluminum"], 10)}), 100,
			StockT({StockUnit(commd["Steel"], 50), StockUnit(commd["Electronics"], 5), StockUnit(commd["Industrial parts"], 50)})),

			IndustryBuilding("High-Tech Rocket Parts Factory", StockT({StockUnit(commd["High-tech rocket parts"], 10)}), 
			StockT({StockUnit(commd["Electronics"], 1), StockUnit(commd["Titanium"], 5), StockUnit(commd["Duraluminium"], 3), StockUnit(commd["Carbon"], 1)}),
			100, StockT({StockUnit(commd["Steel"], 10), StockUnit(commd["Electronics"], 20), StockUnit(commd["Industrial parts"], 100)})),

			IndustryBuilding("Electronics Factory", StockT({StockUnit(commd["Electronics"], 50)}), StockT({StockUnit(commd["Gold"], 2), StockUnit(commd["Silicon"], 10)}),
			10, StockT({StockUnit(commd["Industrial parts"], 20), StockUnit(commd["Steel"], 2),})),

			IndustryBuilding("Power Plant", StockT({StockUnit(commd["Waste"], 5)}), StockT({StockUnit(commd["Carbon"], 20)}),
			-100, StockT({StockUnit(commd["Industrial parts"], 10), StockUnit(commd["Steel"], 20), StockUnit(commd["Electronics"], 5)}))
			});
	}
};