#pragma once

#include <list>
#include <qdatetime.h>

#include "Calc.h"
#include "IndustryBuilding.h"

using BuildingQuantityT = std::pair<IndustryBuilding, uint64_t>;

enum class ConstructionStatus
{
	InConstruction,
	Queue,
	Paused
};

class Construction
{
	size_t buildingID;
	uint64_t cost;
	int64_t amount;
	QDate etc;
	ConstructionStatus status;

public:
	Construction() = delete;
	Construction(const Construction &) = default;
	Construction(Construction &&) = default;
	Construction(size_t buildingID, int64_t amount, QDate etc, ConstructionStatus status = ConstructionStatus::InConstruction)
		:buildingID(buildingID),amount(amount), 
		etc(std::move(etc)), status(status)
	{}
	~Construction() = default;

	Construction & operator=(Construction &) = default;
	Construction & operator=(Construction &&) = default;

	void setAmount(uint32_t newAmount)
	{
		amount = newAmount;
	}
	void setStatus(ConstructionStatus newStatus)
	{
		status = newStatus;
	}
	void setEtc(QDate newEtc)
	{
		etc = newEtc;
	}

	size_t getBuildingID() const
	{
		return buildingID;
	}
	uint64_t getConstructionCost() const
	{
		return cost;
	}
	int64_t getAmount() const
	{
		return amount;
	}
	const QDate & getETC() const
	{
		return etc;
	}
	ConstructionStatus getStatus() const
	{
		return status;
	}

	static QString StatusToQString(ConstructionStatus status)
	{
		switch (status)
		{
		case ConstructionStatus::InConstruction:
			return "In construction";
			break;
		case ConstructionStatus::Queue:
			return "Queue";
			break;
		case ConstructionStatus::Paused:
			return "Paused";
			break;
		default:
			break;
		}
		return "";
	}
};

class Industry
{
	std::vector<BuildingQuantityT> buildings;
	std::list<Construction> constructionQueue;

	void sortBuildings()
	{
		std::sort(buildings.begin(), buildings.end(),
			[](const BuildingQuantityT & a, const BuildingQuantityT & b)->bool
		{
			return a.first.getEnergyConsumption() < b.first.getEnergyConsumption();
		});
	}
	void sortConstructionQueue()
	{
		if (constructionQueue.empty())
			return;

		constructionQueue.sort([](const Construction & a, const Construction & b)->bool
		{
			if (static_cast<int32_t>(a.getStatus()) < static_cast<int32_t>(b.getStatus()))
			{
				return true;
			}
			return false;
		});
		if (constructionQueue.front().getStatus() == ConstructionStatus::Queue)
		{
			constructionQueue.front().setStatus(ConstructionStatus::InConstruction);
		}
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
	Industry(std::vector<BuildingQuantityT> buildings, std::list<Construction> constructionQueue)
		:buildings(std::move(buildings)), constructionQueue(std::move(constructionQueue))
	{
		sortBuildings();
		sortConstructionQueue();
	}
	Industry(const Industry & other) = default;
	Industry(Industry && other) = default;
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
	const std::list<Construction> & getConstructionQueue() const
	{
		return constructionQueue;
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


	void cancelConstruction(size_t index = 0)
	{
		auto elem = constructionQueue.begin();
		std::advance(elem, index);
		constructionQueue.erase(elem);
		sortConstructionQueue();
	}
	void pauseConstruction(size_t index = 0)
	{
		auto elem = constructionQueue.begin();
		std::advance(elem, index);

		elem->setStatus((elem->getStatus() == ConstructionStatus::InConstruction ||
			elem->getStatus() == ConstructionStatus::Queue) ?
			ConstructionStatus::Paused : ConstructionStatus::Queue);

		sortConstructionQueue();
	}
	void addNewConstruction(Construction constr)
	{
		if (!constructionQueue.empty())
		{
			constructionQueue.front().setStatus(ConstructionStatus::Queue);
		}
		constructionQueue.emplace_front(std::move(constr));
	}
	void setConstructionAmount(int64_t amount, size_t index = 0)
	{
		if (amount <= 0)
		{
			cancelConstruction(index);
			return;
		}
		auto elem = constructionQueue.begin();
		std::advance(elem, index);
		elem->setAmount(amount);
	}
	Construction & getConstruction()
	{
		return constructionQueue.front();
	}


	const BuildingQuantityT & operator[](size_t index) const
	{
		return buildings[index];
	}
};