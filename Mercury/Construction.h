#pragma once

#include <list>
#include <qstring.h>

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
	//Estimated completion time in days
	uint64_t etc;
	ConstructionStatus status;

public:
	Construction() = delete;
	Construction(const Construction &) = default;
	Construction(Construction &&) = default;
	Construction(size_t buildingID, int64_t amount, uint64_t etc = 0, uint64_t cost = 0,
		ConstructionStatus status = ConstructionStatus::InConstruction)
		:buildingID(buildingID), amount(amount),
		etc(std::move(etc)), status(status),
		cost(cost)
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
	void setEtc(uint64_t newEtc)
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
	uint64_t getETC() const
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