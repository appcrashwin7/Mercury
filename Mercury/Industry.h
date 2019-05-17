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

	uint64_t getEnergyProduction() const
	{
		uint64_t ret = 0;
		for (const auto & b : Buildings)
		{
			if (b.first.energyProduction.value() > 0)
			{
				ret += ((b.first.energyProduction / units::megawatt) * b.second);
			}
		}
		return ret;
	}
	uint64_t getEnergyDemand() const
	{
		uint64_t ret = 0;
		for (const auto & b : Buildings)
		{
			if (b.first.energyDrain.value() > 0)
			{
				ret += ((b.first.energyDrain / units::megawatt) * b.second);
			}
		}
		return ret;
	}

	const std::vector<BuildingQuantityT> & getBuildings() const
	{
		return Buildings;
	}

	QuantityT getWeeklyUsageOfCommodities(uint64_t days = 7) const
	{
		Commodities commd;
		QuantityT ret(commd.get().size(), 0);
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
							ret[i] += (t.second * building.second * days);
						}
					}
				}
			}
		}
		return ret;
	}
	QuantityT getWeeklyProductionOfCommodities(uint64_t days = 7) const
	{
		Commodities commd;
		QuantityT ret(commd.get().size(), 0);
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
							ret[i] += (t.second * building.second * days);
						}
					}
				}
			}
		}
		return ret;
	}
	uint64_t getWeeklyMinesYield(uint64_t days = 7) const
	{
		auto mine = std::find_if(Buildings.begin(), Buildings.end(), [](const BuildingQuantityT & b)->bool
		{
			if (b.first.name == "Mine")
			{
				return true;
			}
			return false;
		});
		return (MINE_BASE_OUTPUT * mine->second * days);
	}
};