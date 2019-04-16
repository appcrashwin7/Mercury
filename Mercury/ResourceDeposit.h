#pragma once

#include <vector>

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
*/
class ResourceDeposit
{
	std::vector <Deposit> Res;

public:
	ResourceDeposit()
	{
		Res.resize(18);
	}
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
};