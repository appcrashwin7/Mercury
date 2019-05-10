#pragma once

#include <vector>

#include "Product.h"
#include "ResourceDeposit.h"

using StockUnit = std::pair<Product, uint64_t>;
using QuantityT = std::vector<uint64_t>;
using StockT = std::vector<StockUnit>;

class Commodities
{
	std::vector<Product> Commd;

public:
	Commodities()
	{
		auto resNames = ResourceDeposit::getResourcesNames();
		auto massPerUnit = ResourceDeposit::getResourcesDensity();

		for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
		{
			Commd.emplace_back(Product(resNames[i], massPerUnit[i], ProductType::Resource));
		}

		Commd.emplace_back(Product("Waste", 1.5f, ProductType::Dangerous));
		Commd.emplace_back(Product("Steel", 8.0f, ProductType::Material));
		Commd.emplace_back(Product("Stainless steel", 7.5f, ProductType::Material));
		Commd.emplace_back(Product("Duraluminium", 3.0f, ProductType::Material));
		Commd.emplace_back(Product("Electronics", 2.0f, ProductType::Parts));
		Commd.emplace_back(Product("Industrial parts", 4.0f, ProductType::Parts));
		Commd.emplace_back(Product("Rocket parts", 3.5f, ProductType::Parts));
		Commd.emplace_back(Product("High-tech rocket parts", 3.0f, ProductType::Parts));
		Commd.emplace_back(Product("Jewelry", 4.5f, ProductType::Material));
		Commd.emplace_back(Product("Low-enriched uranium", 18.0f, ProductType::Radioactive));
		Commd.emplace_back(Product("Kerosene-LOX", 1.0f, ProductType::Material));
		Commd.emplace_back(Product("Food", 1.5f, ProductType::Organic));
		Commd.emplace_back(Product("Medicine", 1.5f, ProductType::Resource));
	}
	Commodities(const Commodities & other) = delete;
	~Commodities() = default;

	const std::vector<Product> & get() const
	{
		return Commd;
	}
	
	const Product & operator[](const std::string & name)
	{
		auto ret = std::find_if(Commd.begin(), Commd.end(), [&](Product& p)->bool
		{
			if (p.getName() == name)
			{
				return true;
			}
		});

		return ret.operator*();
	}
};