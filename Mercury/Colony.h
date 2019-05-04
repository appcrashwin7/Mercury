#pragma once

#include "Planet.h"
#include "Commodities.h"

class Colony
{
	const Planet & planet;
	StockT Stock;
	QuantityT ResourcesStock;

public:
	Colony() = delete;
	Colony(const Colony & other, const QuantityT & commQuantity = QuantityT(), const QuantityT & resQuantity = QuantityT(18));
	Colony(Planet & onPlanet, const QuantityT & commQuantity = QuantityT(), const QuantityT & resQuantity = QuantityT(18));
	~Colony() = default;

	const Planet & getPlanet() const;
	StockT & getStockpile();
	QuantityT getResourcesStockpile();

private:
	void constructStockpile(const std::vector<uint64_t>& units);
	void defaultStockpile();
};