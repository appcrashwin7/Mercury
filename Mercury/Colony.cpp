#include "Colony.h"

Colony::Colony(RockyBody& on, const QuantityT& commQuantity,
	const QuantityT& buildings, std::list<Construction> constrList)
	:body(on), constructionQueue(std::move(constrList))
{
	constructStockpile(commQuantity);
	colonyIndustry += (buildings);
}

const RockyBody & Colony::getBody() const
{
	return body;
}

const StockT & Colony::getStockpile() const
{
	return stock;
}

StockT & Colony::getStockpile()
{
	return stock;
}

const Industry & Colony::getIndustry() const
{
	return colonyIndustry;
}

Industry & Colony::getIndustry()
{
	return colonyIndustry;
}

QuantityT Colony::getWeeklyResourcesYield() const
{
	auto baseYield = colonyIndustry.getWeeklyMinesYield();
	QuantityT ret;
	for (auto res : body.getResources().get())
	{
		ret.push_back(baseYield * static_cast<double>(res.second));
	}
	return ret;
}

void Colony::simulate()
{
	Energy energyUsed;
	uint64_t constructionCap = 0u;

	simulateIndustry(energyUsed, constructionCap);
	simulateConstruction(energyUsed, constructionCap);
}

const std::list<Construction>& Colony::getConstructionQueue() const
{
	return constructionQueue;
}

void Colony::cancelConstruction(size_t index)
{
	auto elem = constructionQueue.begin();
	std::advance(elem, index);
	constructionQueue.erase(elem);
	sortConstruction();
}

void Colony::pauseConstruction(size_t index)
{
	auto elem = constructionQueue.begin();
	std::advance(elem, index);

	elem->setStatus((elem->getStatus() == ConstructionStatus::InConstruction ||
		elem->getStatus() == ConstructionStatus::Queue) ?
		ConstructionStatus::Paused : ConstructionStatus::Queue);

	sortConstruction();
}

void Colony::addNewConstruction(size_t buildingID, int64_t amount)
{
	uint64_t cost = 0;
	for (auto & res : colonyIndustry.getBuildings()[buildingID].first.getBuildCost())
	{
		cost += res.second;
	}

	if (!constructionQueue.empty())
	{
		constructionQueue.front().setStatus(ConstructionStatus::Queue);
	}
	constructionQueue.emplace_front((Construction(buildingID, amount, 0u, cost)));
	recalcConstructionETC(0u);
}

void Colony::setConstructionAmount(int64_t amount, size_t index)
{
	if (amount <= 0)
	{
		cancelConstruction(index);
		return;
	}
	auto elem = constructionQueue.begin();
	std::advance(elem, index);
	elem->setAmount(amount);
	recalcConstructionETC(index);
}

void Colony::recalcConstructionETC(size_t index)
{
	auto elem = constructionQueue.begin();
	std::advance(elem, index);

    if (colonyIndustry.getConstructionCapability() > 0)
    {
        uint64_t etc = ((elem->getConstructionCost() *
            elem->getAmount()) / colonyIndustry.getConstructionCapability());
        elem->setEtc(etc);
        return;
    }
    elem->setEtc(0);
}

void Colony::sortConstruction()
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

void Colony::constructStockpile(const QuantityT & units)
{
	if (units.empty())
	{
		defaultStockpile();
	}
	else
	{
		Commodities commd;
		for (size_t i = 0; i < commd.get().size(); i++)
		{
			if (i < units.size())
			{
				stock.emplace_back(StockUnit(commd.get()[i], units[i]));
			}
			else
			{
				stock.emplace_back(StockUnit(commd.get()[i], 0));
			}
		}
	}
}

void Colony::defaultStockpile()
{
	Commodities comms;
	for (const auto & prd : comms.get())
	{
		stock.push_back(StockUnit(prd, 0));
	}
}

void Colony::simulateIndustry(Energy & energyUsed, uint64_t & constructionCap)
{
	uint64_t minedResources = 0;
	for (auto & building : colonyIndustry.getBuildings())
	{
		if (energyUsed > Energy() && building.first.getEnergyConsumption() > Energy())
			continue;

		auto buildingProducingNumber = building.second;
		std::vector<std::pair<size_t, uint64_t>> in;
		for (auto & input : building.first.getInput())
		{
			auto max = stock[input.first.id].second / input.second;
			if (max == 0)
			{
				break;
			}
			if (max < buildingProducingNumber)
			{
				buildingProducingNumber = max;
			}

			if (building.first.getEnergyConsumption() > Energy())
			{
				auto maxE = (energyUsed.value() / building.first.getEnergyConsumption().value()) * -1;
				if (maxE < 0)
				{
					break;
				}
				if (maxE < static_cast<int64_t>(buildingProducingNumber))
				{
					buildingProducingNumber = maxE;
				}
			}

			in.emplace_back(std::make_pair(input.first.id, input.second));
		}
		if (buildingProducingNumber > 0)
		{
			if (energyUsed < Energy())
			{
				energyUsed -= (building.first.getEnergyConsumption() * static_cast<int64_t>(buildingProducingNumber));
			}
			else if (energyUsed == Energy())
			{
				energyUsed += (building.first.getEnergyConsumption() * static_cast<int64_t>(buildingProducingNumber));
			}


			for (const auto & i : in)
			{
				auto newStockAm = stock[i.first].second - (i.second * buildingProducingNumber);
				stock[i.first].second = newStockAm;
			}

			for (auto & output : building.first.getOutput())
			{
				stock[output.first.id].second += (output.second * buildingProducingNumber);
			}

			auto minOutput = building.first.getMiningOutput();
			auto constrOutput = building.first.getConstructionCapability();
			if (minOutput > 0)
			{
				minedResources += (minOutput * buildingProducingNumber);
			}
			if (constrOutput > 0)
			{
				constructionCap += (constrOutput * buildingProducingNumber);
			}
		}
	}

	auto res = body.getResources().SubstrAll(minedResources);
	size_t index = 0;
	for (auto i : res)
	{
		stock[index].second += i;
		++index;
	}
}

void Colony::simulateConstruction(Energy used, uint64_t constructionCap)
{
	if (constructionCap == 0u || constructionQueue.empty() == true ||
		constructionQueue.front().getStatus() != ConstructionStatus::InConstruction)
		return;

	if (constructionQueue.front().getAmount() <= 0)
	{
		cancelConstruction();
		simulateConstruction(used, constructionCap);
		return;
	}

	auto & currConstr = constructionQueue.front();
	auto baseCost = colonyIndustry.getBuildings()[currConstr.getBuildingID()].first.getBuildCost();

	//[0] by points
	//[1] by resources
	auto maxConstructionsBy = std::array<uint64_t, 2>{
		constructionCap / currConstr.getConstructionCost(),
			constructionCap / currConstr.getConstructionCost()};

	for (auto & res : baseCost)
	{
		auto max = stock[res.first.id].second / res.second;
		if (max < maxConstructionsBy[1])
		{
			maxConstructionsBy[1] = max;
		}
	}

	if (maxConstructionsBy[1] == 0 || maxConstructionsBy[0] == 0)
	{
		return;
	}

	auto maxConstructions = std::minmax_element(maxConstructionsBy.begin(),
		maxConstructionsBy.end(), std::greater<uint64_t>()).second.operator*();
	auto restConstructions = static_cast<uint64_t>(currConstr.getAmount());
	if (maxConstructions > restConstructions)
	{
		maxConstructions = restConstructions;
	}

	for (const auto & res : baseCost)
	{
		auto newAmount = stock[res.first.id].second -
			(res.second * maxConstructions);
		stock[res.first.id].second = newAmount;
	}

	colonyIndustry.addBuilding(currConstr.getBuildingID(), maxConstructions);
	int64_t newConstrAmount = currConstr.getAmount() - maxConstructions;
	currConstr.setAmount(newConstrAmount);
}
