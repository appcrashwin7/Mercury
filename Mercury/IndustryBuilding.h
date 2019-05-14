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
			IndustryBuilding("Infrastructure", {}, {}, 0, {{commd["Steel"], 2}}),
			IndustryBuilding("Mine", {}, {}, 1, {{commd["Industrial parts"], 5}, {commd["Steel"], 1}}),
			IndustryBuilding("Housing", {}, {}, 1, {{commd["Steel"], 10}}),
			IndustryBuilding("Steel Forge", {{commd["Steel"], 10}}, {{commd["Iron"], 9}, {commd["Carbon"], 1}},
			10, {{commd["Industrial parts"], 40}, {commd["Steel"], 10}}),

			IndustryBuilding("Stainless steel Forge", {{commd["Stainless steel"], 10}},
			{{commd["Iron"], 10}, {commd["Carbon"], 1}}, 45, {{commd["Steel"], 10}, {commd["Industrial parts"], 50}}),

			IndustryBuilding("Duraluminium Forge", {{commd["Duraluminium"], 10}}, {{commd["Aluminum"], 9}, {commd["Copper"], 1}},
			50, {{commd["Industrial parts"], 40}, {commd["Steel"], 10}}),

			IndustryBuilding("Industrial Parts Factory", {{commd["Industrial parts"], 100}},
			{{commd["Steel"], 20}, {commd["Copper"], 5}, {commd["Stainless steel"], 10}, {commd["Aluminum"], 5}, {commd["Lead"], 10}}, 50,
			{{commd["Steel"], 50}, {commd["Lead"], 5}}),

			IndustryBuilding("Rocket Parts Factory", {{commd["Rocket parts"], 50}},
			{{commd["Titanium"], 10}, {commd["Duraluminium"], 5}, {commd["Aluminum"], 10}}, 100,
			{{commd["Steel"], 50}, {commd["Electronics"], 5}, {commd["Industrial parts"], 50}}),

			IndustryBuilding("High-Tech Rocket Parts Factory", {{commd["High-tech rocket parts"], 10}},
			{{commd["Electronics"], 1}, {commd["Titanium"], 5}, {commd["Duraluminium"], 3}, {commd["Carbon"], 1}},
			100, {{commd["Steel"], 10}, {commd["Electronics"], 20}, {commd["Industrial parts"], 100}}),

			IndustryBuilding("Electronics Factory", {{commd["Electronics"], 50}}, {{commd["Gold"], 2}, {commd["Silicon"], 10}},
			10, {{commd["Industrial parts"], 20}, {commd["Steel"], 2}}),

			IndustryBuilding("Power Plant", {{commd["Waste"], 5}}, {{commd["Carbon"], 20}},
			-100, {{commd["Industrial parts"], 10}, {commd["Steel"], 20}, {commd["Electronics"], 5}})
			});
	}
};