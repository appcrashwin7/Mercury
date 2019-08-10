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
	uint32_t constructionCapability;
	//If negative then it take infrastructure
	int32_t infrastructureSupport;

public:
	IndustryBuilding() = delete;
	IndustryBuilding(const IndustryBuilding &) = default;
	IndustryBuilding(IndustryBuilding &&) = default;
	IndustryBuilding(std::string name, StockT input, StockT output, StockT buildCost, 
		Energy energyConsumption, int32_t infrastructure = -1, uint32_t popSupport = 0, uint32_t miningOutput = 0, uint32_t constrCapability = 0)
		:name(std::move(name)), input(std::move(input)), output(std::move(output)),
		buildCost(std::move(buildCost)), energyConsumption(std::move(energyConsumption)),
		miningOutput(miningOutput), populationSupport(popSupport), 
		infrastructureSupport(infrastructure), constructionCapability(constrCapability)
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
	uint32_t getConstructionCapability() const
	{
		return constructionCapability;
	}
	int32_t getInfrastructureSupport() const
	{
		return infrastructureSupport;
	}
};