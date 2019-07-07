#pragma once

#include <tuple>

#include "RockyBody.h"
#include "Industry.h"
#include "Construction.h"

//pair(systemID, bodyID), colony stock, buildings number
using ColonyData = std::tuple<std::pair<size_t, size_t>, QuantityT, QuantityT>;

class Colony
{
	RockyBody & body;
	StockT stock;
	Industry colonyIndustry;
	std::list<Construction> constructionQueue;

public:
	Colony() = delete;
	Colony(const Colony &) = default;
	Colony(Colony &&) = default;
	Colony(RockyBody & on, const QuantityT & commQuantity = QuantityT(), const QuantityT & buildings = QuantityT());
	~Colony() = default;

	const RockyBody & getBody() const;

	const StockT & getStockpile() const;
	StockT & getStockpile();

	const Industry & getIndustry() const;
	Industry & getIndustry();

	QuantityT getWeeklyResourcesYield() const;

	void simulate();

	const std::list<Construction> & getConstructionQueue() const;
	void cancelConstruction(size_t index = 0);
	void pauseConstruction(size_t index = 0);
	void addNewConstruction(size_t buildingID, int64_t amount);
	void setConstructionAmount(int64_t amount, size_t index = 0);

private:
	void sortConstruction();
	void constructStockpile(const QuantityT & units);
	void defaultStockpile();
};