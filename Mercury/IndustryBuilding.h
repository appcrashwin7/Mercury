#pragma once

#include "ResourceDeposit.h"
#include "Commodities.h"

class IndustryBuilding
{
public:
	IndustryBuilding() = delete;
	IndustryBuilding(const IndustryBuilding & other)
		:baseOutput(other.baseOutput), baseInput(other.baseInput), energyDrain(other.energyDrain), baseCost(other.baseCost), resInput(other.resInput)
	{
	};
	IndustryBuilding(const StockT & output, const StockT & input, float drain, const StockT & cost)
		:baseOutput(output), baseInput(input), energyDrain(drain), baseCost(cost)
	{};
	~IndustryBuilding() = default;

	const StockT baseOutput;
	const StockT baseInput;
	const float energyDrain;
	const std::vector<ResQuantity> resInput;

	const StockT baseCost;
};