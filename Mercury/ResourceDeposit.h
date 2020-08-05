#pragma once

#pragma warning(disable: 4146)

#include <vector>
#include <array>

static constexpr size_t RESOURCES_LIST_SIZE = 18;
static constexpr float R_FULL_ACCESS = 1.0f;
static constexpr float R_NON_ACCESS = 0.0f;

//Amount, access
using Deposit = std::pair<uint64_t, float>;

using ResQuantity = std::pair<uint64_t, uint64_t>;

using DepositContainer = std::array<Deposit, RESOURCES_LIST_SIZE>;

class ResourceDeposit
{
	DepositContainer Res = {};

public:
	ResourceDeposit() = default;
	ResourceDeposit(const DepositContainer & otherRes)
		:Res(otherRes)
	{};
	ResourceDeposit(const ResourceDeposit & other) = default;
	ResourceDeposit(ResourceDeposit && other) = default;
	~ResourceDeposit() = default;

	ResourceDeposit & operator=(ResourceDeposit &&) = default;

	std::array<uint64_t, RESOURCES_LIST_SIZE> SubstrAll(uint64_t amount)
	{
		std::array<uint64_t, RESOURCES_LIST_SIZE> ret = {};
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
					auto nRes = Res[i].first - amount;
					Res[i].first = nRes;
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


	static std::array<size_t, 8> getLightElementsIds()
	{
		return { 0, 1, 10, 13, 14, 15, 16, 17 };
	}
	static bool isLightElem(uint id)
	{
		auto lightElements = ResourceDeposit::getLightElementsIds();

		auto elem = std::find(lightElements.begin(), lightElements.end(), id);
		if (elem != lightElements.end())
		{
			return true;
		}
		return false;
	}

	static std::array<std::string, RESOURCES_LIST_SIZE> getResourcesNames()
	{
		return { "Water", "Frozen water", "Aluminum", "Copper", "Gold", "Iron", "Titanium",
			"Lead", "Silver", "Zinc", "Carbon", "Thorium", "Uranium", "Lithium", "Helium", "Sulfur", "Silicon", "Nitrogen" };
	}
	static std::array<float, RESOURCES_LIST_SIZE> getResourcesDensity()
	{
		return { 1.0f, 1.0f, 3.0f, 9.0f, 19.0f, 8.0f, 4.5f,
			11.0f, 7.0f, 2.0f, 3.0f, 12.0f, 18.0f, 0.5f, 0.1f, 2.0f, 2.3f, 0.8f };
	}


	const DepositContainer & get() const
	{
		return Res;
	}
	const Deposit & operator[](size_t i) const
	{
		return Res[i];
	}
	Deposit& operator[](size_t i)
	{
		return Res[i];
	}
};