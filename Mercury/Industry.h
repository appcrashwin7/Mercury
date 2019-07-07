#pragma once

#include "Calc.h"
#include "IndustryBuilding.h"

using BuildingQuantityT = std::pair<IndustryBuilding, uint64_t>;

class Industry
{
	std::vector<BuildingQuantityT> buildings;

	void sortBuildings()
	{
		std::sort(buildings.begin(), buildings.end(),
			[](const BuildingQuantityT & a, const BuildingQuantityT & b)->bool
		{
			return a.first.getEnergyConsumption() < b.first.getEnergyConsumption();
		});
	}
public:
	Industry()
	{
		auto def = IndustryBuilding::getDefaults();
		for (auto & b : def)
		{
			buildings.emplace_back(BuildingQuantityT(b, 0));
		}

		sortBuildings();
	}
	Industry(const Industry &) = default;
	Industry(Industry &&) = default;
	Industry(std::vector<BuildingQuantityT> buildings)
		:buildings(std::move(buildings))
	{
		sortBuildings();
	}
	~Industry() = default;

	Industry & operator=(const Industry & other)
	{
		buildings.clear();
		for (auto & i : other.buildings)
		{
			buildings.emplace_back(BuildingQuantityT(i.first, i.second));
		}

		return *this;
	}
	Industry & operator+=(const QuantityT & buildingAmount)
	{
		if (!buildingAmount.empty())
		{
			for (size_t i = 0; i < buildings.size(); i++)
			{
				if (i == buildingAmount.size())
				{
					break;
				}
				buildings[i].second += buildingAmount[i];
			}
		}
		return *this;
	}

	uint64_t getEnergyProduction() const
	{
		uint64_t ret = 0;
		for (const auto & b : buildings)
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
		for (const auto & b : buildings)
		{
			if (b.first.getEnergyConsumption() > Energy())
			{
				ret += ((b.first.getEnergyConsumption() / units::megawatt) * b.second);
			}
		}
		return ret;
	}
	uint64_t getConstructionCapability() const
	{
		uint64_t ret = 0;
		for (const auto & b : buildings)
		{
			ret += (b.first.getConstructionCapability() * b.second);
		}
		return ret;
	}

	const std::vector<BuildingQuantityT> & getBuildings() const
	{
		return buildings;
	}

	QuantityT getWeeklyUsageOfCommodities(uint64_t days = 7) const
	{
		Commodities commd;
		QuantityT ret(commd.get().size(), 0);
		for (const auto & building : buildings)
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
		for (const auto & building : buildings)
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
		for (const auto & b : buildings)
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
		buildings[index].second += amount;
	}
	void removeBuilding(size_t index, uint64_t amount = 1)
	{
		buildings[index].second -= amount;
	}

	const BuildingQuantityT & operator[](size_t index) const
	{
		return buildings[index];
	}
};