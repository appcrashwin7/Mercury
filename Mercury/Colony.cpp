#include "Colony.h"

Colony::Colony(const Colony & other, const QuantityT & commQuantity, const QuantityT & resQuantity)
	:planet(other.planet), ResourcesStock(resQuantity)
{
	constructStockpile(commQuantity);
}

Colony::Colony(Planet & onPlanet, const QuantityT & commQuantity, const QuantityT & resQuantity)
	:planet(onPlanet), ResourcesStock(resQuantity)
{
	constructStockpile(commQuantity);
}

const Planet & Colony::getPlanet() const
{
	return planet;
}

StockT & Colony::getStockpile()
{
	return Stock;
}

QuantityT Colony::getResourcesStockpile()
{
	return ResourcesStock;
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
	for (const auto & prd : comms.get())
	{
		Stock.push_back(StockUnit(prd, 0));
	}
}
