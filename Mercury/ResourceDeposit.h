#pragma once

#pragma warning(disable: 4146)

#include <vector>
#include <array>


//Amount, accessibly
using Deposit = std::pair<uint64_t, float>;
using ResQuantity = std::pair<uint64_t, uint64_t>;


static constexpr size_t RESOURCES_LIST_SIZE = 18;


class ResourceDeposit
{
	std::vector<Deposit> Res = std::vector<Deposit>(RESOURCES_LIST_SIZE, std::allocator<Deposit>());

public:
	ResourceDeposit() = default;
	ResourceDeposit(const ResourceDeposit & other) = default;
	ResourceDeposit(ResourceDeposit && other) = default;
	~ResourceDeposit() = default;

	void replace(const ResourceDeposit & other)
	{
		for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
		{
			Res[i] = other.get()[i];
		}
	}

	std::vector<uint64_t> SubstrAll(uint64_t amount)
	{
		std::vector<uint64_t> ret(RESOURCES_LIST_SIZE, {});
		for (size_t i = 0; i < Res.size(); i++)
		{
			if (Res[i].first > 0)
			{
				if (amount > Res[i].first)
				{
					Res[i].first = 0;
					ret[i] = (Res[i].first);
				}
				else
				{
					Res[i].first =- amount;
					ret[i] = amount;
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

	static std::vector<size_t> getLightElementsIds()
	{
		return std::vector<size_t>({ 0, 1, 10, 13, 14, 15, 16, 17 });
	}
	static std::vector<std::string> getResourcesNames()
	{
		return std::vector<std::string>({ "Water", "Frozen water", "Aluminum", "Copper", "Gold", "Iron", "Titanium",
			"Lead", "Silver", "Zinc", "Carbon", "Thorium", "Uranium", "Lithium", "Helium", "Sulfur", "Silicon", "Nitrogen" });
	}
	static std::array<float, RESOURCES_LIST_SIZE> getResourcesDensity()
	{
		return std::array<float, RESOURCES_LIST_SIZE>({ 1.0f, 1.0f, 3.0f, 9.0f, 19.0f, 8.0f, 4.5f,
			11.0f, 7.0f, 2.0f, 3.0f, 12.0f, 18.0f, 0.5f, 0.1f, 2.0f, 2.3f, 0.8f });
	}

	const std::vector<Deposit> & get() const
	{
		return Res;
	}
	const Deposit & operator[](size_t i) const
	{
		return Res[i];
	}
};