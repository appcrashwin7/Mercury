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
	if (colonyIndustry.getEnergyProduction() < colonyIndustry.getEnergyDemand())
		return;

	auto res = body.getResources().SubstrAll(colonyIndustry.getWeeklyMinesYield(1));
	size_t index = 0;
	for (auto i : res)
	{
		stock[index].second += i;
		++index;
	}

	for (auto & building : colonyIndustry.getBuildings())
	{
		size_t buildingProducingNumber = building.second;

		std::vector<std::pair<size_t, uint64_t>> in;
		for (auto & input : building.first.baseInput)
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

			in.emplace_back(std::make_pair(input.first.id, input.second));
		}
		if (buildingProducingNumber > 0)
		{
			for (const auto & i : in)
			{
				auto newStockAm = stock[i.first].second - (i.second * buildingProducingNumber);
				stock[i.first].second = newStockAm;
			}

			for (auto & output : building.first.baseOutput)
			{
				stock[output.first.id].second += (output.second * buildingProducingNumber);
			}
		}
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
