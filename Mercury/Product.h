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
	const std::string name;
	const float massPerUnit;
	const ProductType type;

public:
	Product() = delete;
	Product(const Product & other) = default;
	Product(const std::string & pname, float mass, ProductType t)
		:name(pname), massPerUnit(mass), type(t)
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

	const std::string & getName() const
	{
		return name;
	}
	float getMassPerUnit() const
	{
		return massPerUnit;
	}
	ProductType getType() const
	{
		return type;
	}
};