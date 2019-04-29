#pragma once

#include <vector>

#include "Product.h"

typedef std::pair<Product, uint64_t> StockUnit;
typedef std::vector<StockUnit> StockT;

class Commodities
{
	std::vector<Product> Commd;

public:
	Commodities()
	{
		Commd.push_back(Product("Water", 1.0f, ProductType::Resource));
		Commd.push_back(Product("Heavy water", 1.1f, ProductType::Resource));
		Commd.push_back(Product("Waste", 1.5f, ProductType::Dangerous));
		Commd.push_back(Product("Steel", 7.8f, ProductType::Material));
		Commd.push_back(Product("Stainless steel", 7.5f, ProductType::Material));
		Commd.push_back(Product("Duraluminium", 2.7f, ProductType::Material));
		Commd.push_back(Product("Electronics", 2.0f, ProductType::Parts));
		Commd.push_back(Product("Industrial parts", 4.0f, ProductType::Parts));
		Commd.push_back(Product("Rocket parts", 3.5f, ProductType::Parts));
		Commd.push_back(Product("High-tech rocket parts", 3.0f, ProductType::Parts));
		Commd.push_back(Product("Jewerly", 4.5f, ProductType::Material));
		Commd.push_back(Product("Low-enriched uranium", 18.0f, ProductType::Radioactive));
		Commd.push_back(Product("Kerosine-LOX", 1.0f, ProductType::Material));
		Commd.push_back(Product("Food", 1.5f, ProductType::Organic));
		Commd.push_back(Product("Medicine", 1.5f, ProductType::Resource));
	}
	Commodities(const Commodities & other) = delete;
	~Commodities() = default;

	const std::vector<Product> & get() const
	{
		return Commd;
	}
};