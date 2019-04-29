#include "Colony.h"

Colony::Colony(const Colony & other, const std::vector<uint64_t> & quantity)
	:planet(other.planet)
{
	constructStockpile(quantity);
}

Colony::Colony(Planet & onPlanet, const std::vector<uint64_t> & quantity)
	:planet(onPlanet)
{
	constructStockpile(quantity);
}

const Planet & Colony::getPlanet() const
{
	return planet;
}

StockT & Colony::getStockpile()
{
	return Stock;
}

void Colony::constructStockpile(const std::vector<uint64_t>& units)
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
				Stock.push_back(StockUnit(commd.get()[i], units[i]));
			}
			else
			{
				Stock.push_back(StockUnit(commd.get()[i], 0));
			}
		}
	}
}

void Colony::defaultStockpile()
{
	Commodities comms;
	for (auto prd : comms.get())
	{
		Stock.push_back(StockUnit(prd, 0));
	}
}
