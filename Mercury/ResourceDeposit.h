#pragma once

#include <vector>
#include <array>

//Amount, accessibly
typedef std::pair<uint64_t, float> Deposit;

/*
Resources
1.Water
2.Frozen water
3.Aluminium
4.Copper
5.Gold
6.Iron
7.Titanium
8.Lead
9.Silver
10.Zinc
11.Carbon
12.Thorium
13.Uranium
14.Lithium
15.Helium
16.Sulfur
17.Silicon
18.Nitrogen
//In tons
*/
class ResourceDeposit
{
	std::vector<Deposit> Res;

public:
	ResourceDeposit()
	{
		Res.resize(18);
	}
	ResourceDeposit(const ResourceDeposit & other)
		:Res(other.Res)
	{}
	~ResourceDeposit() = default;


	std::vector<uint64_t> SubstrAll(uint64_t amount)
	{
		std::vector<uint64_t> ret;
		ret.resize(18);
		for (size_t i = 0; i < Res.size(); i++)
		{
			if (Res[i].first > 0)
			{
				if (amount > Res[i].first)
				{
					Res[i].first = 0;
					ret[i] = (Res[i].first + (Res[i].first * Res[i].second));
				}
				else
				{
					Res[i].first =- amount;
					ret[i] = (amount + (amount * Res[i].second));
				}
			}
		}
		return ret;
	}

	Deposit & editDeposit(size_t id)
	{
		return Res[id];
	}
	const Deposit & accessDeposit(size_t id) const
	{
		return Res[id];
	}

	bool isEmpty() const
	{
		for (auto i : Res)
		{
			if (i.first > 0)
			{
				return false;
			}
		}
		return  true;
	}
	bool isNotGenerated() const
	{
		for (auto i : Res)
		{
			if (i.first > 0 || i.second > 0)
			{
				return false;
			}
		}
		return true;
	}

	static const std::vector<unsigned int> getLightElementsIds()
	{
		return std::vector<unsigned int>({ 1, 2, 11, 14, 15, 16, 17, 18 });
	}
	static const std::vector<std::string> getResourcesNames()
	{
		return std::vector<std::string>({ "Water", "Frozen water","Aluminium","Copper","Gold","Iron","Titanium"
			,"Lead","Silver","Zinc","Carbon","Thorium","Uranium","Lithium","Helium","Sulfur","Silicon","Nitrogen" });
	}

	const std::vector<Deposit> & getRes() const
	{
		return Res;
	}
};