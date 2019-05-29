#pragma once

#include "Planet.h"
#include "Industry.h"

class Colony
{
	Planet & planet;
	StockT stock;
	Industry colonyIndustry;

public:
	Colony() = delete;
	Colony(const Colony & other) = default;
	Colony(Colony && other) = default;
	Colony(Planet & onPlanet, const QuantityT & commQuantity = QuantityT(), const QuantityT & buildings = QuantityT());
	~Colony() = default;

	const Planet & getPlanet() const;

	const StockT & getStockpile() const;
	StockT & getStockpile();

	const Industry & getIndustry() const;
	Industry & getIndustry();

	QuantityT getWeeklyResourcesYield() const;

private:
	void constructStockpile(const QuantityT & units);
	void defaultStockpile();
};