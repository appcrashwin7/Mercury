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
	IndustryBuilding(const std::string & name, const StockT & output, const StockT & input, float drain, const StockT & cost)
		:baseOutput(output), baseInput(input), energyDrain(drain), baseCost(cost)
	{};
	~IndustryBuilding() = default;

	const std::string name;
	const StockT baseOutput;
	const StockT baseInput;
	//In megawatts, value lower than 0 mean that building is actually producing energy
	const float energyDrain;

	const StockT baseCost;

	static std::vector<IndustryBuilding> getDefaultBuildings()
	{
		Commodities commd;
		return std::vector<IndustryBuilding>({
			IndustryBuilding("Infrastructure", StockT(), StockT(), 0.0f, StockT({StockUnit(commd["Steel"], 2)})),
			IndustryBuilding("Mine", StockT(), StockT(), 1.0f, StockT({StockUnit(commd["Industrial parts"], 5), StockUnit(commd["Steel"], 1)})),
			IndustryBuilding("Housing", StockT(), StockT(), 0.5f, StockT({StockUnit(commd["Steel"], 10)})),
			IndustryBuilding("Steel Forge", StockT({StockUnit(commd["Steel"], 4)}), StockT({StockUnit(commd["Iron"], 3), StockUnit(commd["Carbon"], 1)}), 
			10.0f, StockT({StockUnit(commd["Industrial Parts"], 10), StockUnit(commd["Steel"], 5)})),
			IndustryBuilding("Power Plant", StockT({StockUnit(commd["Waste"], 5)}), StockT({StockUnit(commd["Carbon"], 20)}), 
			-100.0f, StockT({StockUnit(commd["Industrial parts"], 10), StockUnit(commd["Steel"], 20), StockUnit(commd["Electronic"], 5)}))
			});
	};
};