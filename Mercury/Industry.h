#pragma once

#include "Calc.h"
#include "IndustryBuilding.h"

using BuildingQuantityT = std::pair<IndustryBuilding, uint64_t>;

class Industry
{
	std::vector<BuildingQuantityT> Buildings;

public:
	Industry()
	{
		auto buildingList = IndustryBuilding::getDefaultBuildings();
		for (auto & b : buildingList)
		{
			Buildings.emplace_back(BuildingQuantityT(b, 0));
		}
	}
	Industry(const Industry & other) = default;
	~Industry() = default;

	float getEnergyProduction() const
	{
		float ret = 0.0f;
		for (const auto & b : Buildings)
		{
			if (b.first.energyDrain != 0 && b.first.energyDrain < 0)
			{
				ret += (b.first.energyDrain * b.second);
			}
		}
		ret *= -1;
		return ret;
	}
	float getEnergyDemand() const
	{
		float ret = 0.0f;
		for (const auto & b : Buildings)
		{
			if (b.first.energyDrain != 0 && b.first.energyDrain > 0)
			{
				ret += (b.first.energyDrain * b.second);
			}
		}
		return ret;
	}

	const std::vector<BuildingQuantityT> & getBuildings() const
	{
		return Buildings;
	}
	//std::vector<uint64_t> getWeeklyUsageOfCommodities() const
	//{}
	//std::vector<uint64_t> getWeeklyProductionOfCommodities() const
	//{}
};