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
