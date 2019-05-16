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
			Buildings.emplace_back(BuildingQuantityT(b, 2));
		}
	}
	Industry(const Industry & other) = default;
	~Industry() = default;

	float getEnergyProduction() const
	{
		float ret = 0.0f;
		for (const auto & b : Buildings)
		{
			if (b.first.energyDrain < 0)
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
	std::vector<uint64_t> getWeeklyUsageOfCommodities() const
	{
		Commodities commd;
		std::vector<uint64_t> ret(commd.get().size(), 0);
		for (const auto & building : Buildings)
		{
			if (building.second > 0)
			{
				for (auto t : building.first.baseInput)
				{
					for (size_t i = 0; i < ret.size(); i++)
					{
						if (t.first == commd.get()[i])
						{
							ret[i] += (t.second * building.second);
						}
					}
				}
			}
		}
		return ret;
	}
	std::vector<uint64_t> getWeeklyProductionOfCommodities() const
	{
		Commodities commd;
		std::vector<uint64_t> ret(commd.get().size(), 0);
		for (const auto & building : Buildings)
		{
			if (building.second > 0)
			{
				for (auto t : building.first.baseOutput)
				{
					for (size_t i = 0; i < ret.size(); i++)
					{
						if (t.first == commd.get()[i])
						{
							ret[i] += (t.second * building.second);
						}
					}
				}
			}
		}
		return ret;
	}
};