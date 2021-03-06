#pragma once

#include <vector>

#include "JsonDataFile.h"
#include "Product.h"
#include "ResourceDeposit.h"

using StockUnit = std::pair<Product, uint64_t>;
using QuantityT = std::vector<uint64_t>;
using StockT = std::vector<StockUnit>;

class Commodities
{
	static inline std::vector<Product> Commd;
    static const inline QString fileData = "Products.json";

public:
	Commodities() = default;
	~Commodities() = default;

	static const std::vector<Product> & get()
	{
		return Commd;
	}
	
	static void load()
	{
		auto resNames = ResourceDeposit::getResourcesNames();
		auto massPerUnit = ResourceDeposit::getResourcesDensity();

		for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
		{
			Commd.emplace_back(Product(resNames[i], massPerUnit[i], ProductType::Resource, i));
		}
		auto lastID = Commd.size() - 1;

        JsonDataFile dtFile;
		if (dtFile.load(Commodities::fileData))
		{
            auto doc = dtFile.get();

			if (doc.isArray())
			{
				for (int i = 0; i < doc.array().size(); i++)
				{
					if (doc[i].isObject())
					{
						if (!(doc[i]["name"].isUndefined() &&
							doc[i]["mass"].isUndefined() &&
							doc[i]["type"].isUndefined()))
						{
							auto name = doc[i]["name"].toString();
							auto mass = static_cast<float>(doc[i]["mass"].toDouble());
							auto type = static_cast<ProductType>(doc[i]["type"].toInt());

							Commd.emplace_back(Product(name.toStdString(), mass, type, lastID + i));
						}
					}
				}
			}
		}
	}

    static const Product& find(const std::string& productName)
    {
        auto ret = std::find_if(Commd.begin(), Commd.end(), [&](Product& p)->bool
            {
                if (p.name == productName)
                {
                    return true;
                }
                return false;
            });
        if (ret == Commd.end())
        {
            std::string error = "Cannot find Product with name: " + productName;
            qFatal(error.c_str());
        }
        return ret.operator*();
    }
};