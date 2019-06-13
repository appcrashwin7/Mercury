#pragma once

#include <tuple>

#include "RockyBody.h"
#include "Industry.h"

//pair(systemID, bodyID), colony stock, buildings number
using ColonyData = std::tuple<std::pair<size_t, size_t>, QuantityT, QuantityT>;

class Colony
{
	RockyBody & body;
	StockT stock;
	Industry colonyIndustry;

public:
	Colony() = delete;
	Colony(const Colony & other) = default;
	Colony(Colony && other) = default;
	Colony(RockyBody & on, const QuantityT & commQuantity = QuantityT(), const QuantityT & buildings = QuantityT());
	~Colony() = default;

	const RockyBody & getBody() const;

	const StockT & getStockpile() const;
	StockT & getStockpile();

	const Industry & getIndustry() const;
	Industry & getIndustry();

	QuantityT getWeeklyResourcesYield() const;

private:
	void constructStockpile(const QuantityT & units);
	void defaultStockpile();
};