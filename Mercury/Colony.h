#pragma once

#include "Planet.h"
#include "Commodities.h"

class Colony
{
	const Planet & planet;
	StockT Stock;

public:
	Colony() = delete;
	Colony(const Colony & other, const std::vector<uint64_t> & quantity = std::vector<uint64_t>());
	Colony(Planet & onPlanet, const std::vector<uint64_t> & quantity = std::vector<uint64_t>());
	~Colony() = default;

	const Planet & getPlanet() const;
	StockT & getStockpile();

private:
	void constructStockpile(const std::vector<uint64_t>& units);
	void defaultStockpile();
};