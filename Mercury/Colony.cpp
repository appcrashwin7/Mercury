#include "Colony.h"

Colony::Colony(RockyBody & on, const QuantityT & commQuantity, const QuantityT & buildings)
	:body(on)
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
		ret.push_back(baseYield * res.second);
	}
	return ret;
}

void Colony::simulate()
{
	Energy energyUsed;
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
			if (minOutput > 0)
			{
				minedResources += (minOutput * buildingProducingNumber);
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
