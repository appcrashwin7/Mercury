#pragma once

#include "Planet.h"
#include "Industry.h"

class Colony
{
	const Planet & planet;
	StockT stock;
	QuantityT resourcesStock;
	Industry colonyIndustry;

public:
	Colony() = delete;
	Colony(const Colony & other, const QuantityT & commQuantity = QuantityT(), const QuantityT & resQuantity = QuantityT(RESOURCES_LIST_SIZE));
	Colony(Planet & onPlanet, const QuantityT & commQuantity = QuantityT(), const QuantityT & resQuantity = QuantityT(RESOURCES_LIST_SIZE));
	~Colony() = default;

	const Planet & getPlanet() const;
	const StockT & getStockpile() const;
	StockT & getStockpile();
	QuantityT getResourcesStockpile();
	const Industry & getIndustry() const;
	Industry & getIndustry();

	QuantityT getWeeklyResourcesYield() const;

private:
	void constructStockpile(const std::vector<uint64_t>& units);
	void defaultStockpile();
};