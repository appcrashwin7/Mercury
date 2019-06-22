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
		auto buildings = IndustryBuilding::getDefaults();
		for (auto & b : buildings)
		{
			Buildings.emplace_back(BuildingQuantityT(b, 0));
		}

		std::sort(Buildings.begin(), Buildings.end(), 
			[](const BuildingQuantityT & a, const BuildingQuantityT & b)->bool
		{
			return a.first.getEnergyConsumption() < b.first.getEnergyConsumption();
		});
	}
	Industry(const Industry & other) = default;
	Industry(Industry && other) = default;
	~Industry() = default;

	Industry & operator=(const Industry & other)
	{
		Buildings.clear();
		for (auto & i : other.Buildings)
		{
			Buildings.emplace_back(BuildingQuantityT(i.first, i.second));
		}

		return *this;
	}
	Industry & operator+=(const QuantityT & buildingAmount)
	{
		if (!buildingAmount.empty())
		{
			for (size_t i = 0; i < Buildings.size(); i++)
			{
				if (i == buildingAmount.size())
				{
					break;
				}
				Buildings[i].second += buildingAmount[i];
			}
		}
		return *this;
	}

	uint64_t getEnergyProduction() const
	{
		uint64_t ret = 0;
		for (const auto & b : Buildings)
		{
			if (b.first.getEnergyConsumption() < Energy())
			{
				ret += (((b.first.getEnergyConsumption() * static_cast<int64_t>(-1)) / units::megawatt) * b.second);
			}
		}
		return ret;
	}
	uint64_t getEnergyDemand() const
	{
		uint64_t ret = 0;
		for (const auto & b : Buildings)
		{
			if (b.first.getEnergyConsumption() > Energy())
			{
				ret += ((b.first.getEnergyConsumption() / units::megawatt) * b.second);
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
				for (auto t : building.first.getInput())
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
				for (auto t : building.first.getOutput())
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
		uint64_t ret = 0;
		for (const auto & b : Buildings)
		{
			auto out = b.first.getMiningOutput();
			if (b.second > 0 && out > 0)
			{
				ret += (out * b.second * days);
			}
		}
		return ret;
	}

	void addBuilding(size_t index, uint64_t amount = 1)
	{
		Buildings[index].second += amount;
	}
	void removeBuilding(size_t index, uint64_t amount = 1)
	{
		Buildings[index].second -= amount;
	}


	const BuildingQuantityT & operator[](size_t index) const
	{
		return Buildings[index];
	}
};