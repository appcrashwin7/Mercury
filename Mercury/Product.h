#pragma once

#include <string>

enum class ProductType
{
	Resource,
	Material,
	Dangerous,
	Gaseous,
	Parts,
	Electronic,
	Organic,
	Radioactive
};

class Product
{
public:
	const std::string name;
	const float massPerUnit;
	const ProductType type;
	const size_t id;

	Product() = delete;
	Product(const Product & other) = default;
	Product(Product &&) = default;
	Product(std::string pname, float mass, ProductType t, size_t id)
		:name(std::move(pname)), massPerUnit(mass), type(t), id(id)
	{}
	~Product() = default;

	bool operator==(const Product & other) const
	{
		if (name == other.name)
		{
			if (type == other.type)
			{
				return true;
			}
		}
		return false;
	}
};