#pragma once

#include "ResourceDeposit.h"
#include "Commodities.h"

class IndustryBuilding
{
	std::string name;

	StockT output;
	StockT input;
	StockT buildCost;

	Energy energyConsumption;

	uint32_t miningOutput;
	uint32_t populationSupport;
	//If negative then it take infrastructure
	int32_t infrastructureSupport;

public:
	IndustryBuilding() = delete;
	IndustryBuilding(const IndustryBuilding &) = default;
	IndustryBuilding(IndustryBuilding &&) = default;
	IndustryBuilding(std::string name, StockT input, StockT output, StockT buildCost, 
		Energy energyConsumption, int32_t infrastructure = -1, uint32_t popSupport = 0, uint32_t miningOutput = 0)
		:name(std::move(name)), input(std::move(input)), output(std::move(output)),
		buildCost(std::move(buildCost)), energyConsumption(std::move(energyConsumption)),
		miningOutput(miningOutput), populationSupport(popSupport), 
		infrastructureSupport(infrastructure)
	{}
	~IndustryBuilding() = default;

	IndustryBuilding & operator=(IndustryBuilding &&) = default;


	const std::string & getName() const
	{
		return name;
	}
	const StockT & getInput() const
	{
		return input;
	}
	const StockT & getOutput() const
	{
		return output;
	}
	const StockT & getBuildCost() const
	{
		return buildCost;
	}
	Energy getEnergyConsumption() const
	{
		return energyConsumption;
	}
	uint32_t getMiningOutput() const
	{
		return miningOutput;
	}
	uint32_t getPopulationSupport() const
	{
		return populationSupport;
	}
	int32_t getInfrastructureSupport() const
	{
		return infrastructureSupport;
	}


	static std::vector<IndustryBuilding> getDefaults()
	{
		Commodities commd;
		return std::vector<IndustryBuilding>({
			IndustryBuilding("Infrastructure", {}, {}, {{commd["Steel"], 2}}, 0, 10),
			IndustryBuilding("Mine", {}, {}, {{commd["Industrial parts"], 5}, {commd["Steel"], 1}}, 1 * units::megawatt, 1, 0, 10),
			IndustryBuilding("Housing", {}, {}, {{commd["Steel"], 10}}, 0, -1, 1000),

			IndustryBuilding("Power Plant",  {{commd["Carbon"], 20}}, {{commd["Waste"], 5}},
			{{commd["Industrial parts"], 10}, {commd["Steel"], 20}, {commd["Electronics"], 5}}, (-100) * units::megawatt),

			IndustryBuilding("Steel Forge", {{commd["Iron"], 9}, {commd["Carbon"], 1}}, {{commd["Steel"], 10}},
			{{commd["Industrial parts"], 40}, {commd["Steel"], 10}}, 10 * units::megawatt),

			IndustryBuilding("Stainless steel Forge", {{commd["Iron"], 10}, {commd["Carbon"], 1}}, {{commd["Stainless steel"], 10}},
			{{commd["Steel"], 10}, {commd["Industrial parts"], 50}}, 45 * units::megawatt),

			IndustryBuilding("Duraluminium Forge", {{commd["Aluminum"], 9}, {commd["Copper"], 1}}, {{commd["Duraluminium"], 10}},
				{{commd["Industrial parts"], 40}, {commd["Steel"], 10}}, 50 * units::megawatt),

			IndustryBuilding("Industrial Parts Factory", {{commd["Steel"], 20}, {commd["Copper"], 5},
				{commd["Stainless steel"], 10}, {commd["Aluminum"], 5}, {commd["Lead"], 10}},
				{{commd["Industrial parts"], 100}}, {{commd["Steel"], 50}, {commd["Lead"], 5}}, 50 * units::megawatt),

			IndustryBuilding("Rocket Parts Factory", {{commd["Titanium"], 10}, {commd["Duraluminium"], 5}, {commd["Aluminum"], 10}},
				{{commd["Rocket parts"], 50}}, {{commd["Steel"], 50}, {commd["Electronics"], 5}, {commd["Industrial parts"], 50}},
				100 * units::megawatt),

			IndustryBuilding("High-Tech Rocket Parts Factory",
			{{commd["Electronics"], 1}, {commd["Titanium"], 5}, {commd["Duraluminium"], 3}, {commd["Carbon"], 1}},
			{{commd["High-tech rocket parts"], 10}}, {{commd["Steel"], 10}, {commd["Electronics"], 20}, {commd["Industrial parts"], 100}},
			100 * units::megawatt),

			IndustryBuilding("Electronics Factory", {{commd["Gold"], 2}, {commd["Silicon"], 10}},
			 {{commd["Electronics"], 50}}, {{commd["Industrial parts"], 20}, {commd["Steel"], 2}},
			 10 * units::megawatt)
			});
	}
};