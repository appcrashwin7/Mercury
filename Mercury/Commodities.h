#pragma once

#include <vector>
#include <qglobal.h>

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
			Commd.emplace_back(Product(resNames[i], massPerUnit[i], ProductType::Resource, i));
		}

		Commd.emplace_back(Product("Waste", 1.5f, ProductType::Dangerous, RESOURCES_LIST_SIZE));
		Commd.emplace_back(Product("Steel", 8.0f, ProductType::Material, RESOURCES_LIST_SIZE + 1));
		Commd.emplace_back(Product("Stainless steel", 7.5f, ProductType::Material, RESOURCES_LIST_SIZE + 2));
		Commd.emplace_back(Product("Duraluminium", 3.0f, ProductType::Material, RESOURCES_LIST_SIZE + 3));
		Commd.emplace_back(Product("Electronics", 2.0f, ProductType::Parts, RESOURCES_LIST_SIZE + 4));
		Commd.emplace_back(Product("Industrial parts", 4.0f, ProductType::Parts, RESOURCES_LIST_SIZE + 5));
		Commd.emplace_back(Product("Rocket parts", 3.5f, ProductType::Parts, RESOURCES_LIST_SIZE + 6));
		Commd.emplace_back(Product("High-tech rocket parts", 3.0f, ProductType::Parts, RESOURCES_LIST_SIZE + 7));
		Commd.emplace_back(Product("Jewelry", 4.5f, ProductType::Material, RESOURCES_LIST_SIZE + 8));
		Commd.emplace_back(Product("Low-enriched uranium", 18.0f, ProductType::Radioactive, RESOURCES_LIST_SIZE + 9));
		Commd.emplace_back(Product("Kerosene-LOX", 1.0f, ProductType::Material, RESOURCES_LIST_SIZE + 10));
		Commd.emplace_back(Product("Food", 1.5f, ProductType::Organic, RESOURCES_LIST_SIZE + 11));
		Commd.emplace_back(Product("Medicine", 1.5f, ProductType::Resource, RESOURCES_LIST_SIZE + 12));
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
			if (p.name == name)
			{
				return true;
			}
			return false;
		});
		if (ret == Commd.end())
		{
			std::string error = "Cannot find Product with name: " + name;
			qFatal(error.c_str());
		}
		return ret.operator*();
	}
};