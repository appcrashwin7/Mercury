#pragma once

#include <optional>

#include "Orbit.h"
#include "PhysicalProperties.h"
#include "ResourceDeposit.h"

enum class CelestialBodyType
{
	Star,
	Planet,
	GasGiant,
	Asteroid
};

static constexpr double MEAN_DENSITY = 3000.0;
static constexpr double BODY_MASS_TO_DEPOSIT_SIZE_MULT = 1e-16;

class CelestialBody
{

	QString name;
public:
	const CelestialBodyType type;
	const Orbit orbit;
	const PhysicalProperties physics;
	const Velocity escapeVelocity;
 	const Acceleration surfaceGravity;


	CelestialBody() = delete;
	CelestialBody(CelestialBody &&) noexcept = default;
	CelestialBody(const CelestialBody & other) = default;
	CelestialBody(PhysicalProperties properties, CelestialBodyType type, ResourceDeposit res = ResourceDeposit(), Orbit orb = Orbit(), QString name = "")
		:physics(std::move(properties)),
		escapeVelocity(Calc::getEscapeVelocity(physics.mass, physics.radius)),
		surfaceGravity(Calc::getGravity(physics.mass, physics.radius)),
		resources(res), type(type),
		orbit(orb), name(std::move(name))
	{
	}
	CelestialBody(const CelestialBody& other, CelestialBodyType newType)
		:physics(other.physics),
		escapeVelocity(other.escapeVelocity),
		surfaceGravity(other.surfaceGravity),
		resources(other.resources),
		type(newType), orbit(other.orbit),
		name(other.name)
	{
	}
	virtual ~CelestialBody() = default;


	void setName(QString newName)
	{
		name = std::move(newName);
	}
	const QString & getName() const
	{
		return name;
	}

	const ResourceDeposit& getResources() const
	{
		return resources;
	}
	ResourceDeposit& getResources()
	{
		return resources;
	}

protected:
	ResourceDeposit resources;

	//Return first - light elements access, second - heavy ...
	static std::pair<float, float> getResourcesAccessByDensity(CelestialBody& body)
	{
		std::pair<float, float> ret;
		auto bdensity = body.physics.getDensity();

		if (bdensity > MEAN_DENSITY)
		{
			double heavyElementsBonus = (bdensity - MEAN_DENSITY) / 1000.0;
			double lightElementsAccessPen = heavyElementsBonus / 10.0;
			ret.first = Calc::roundToDecimalPlace<float>(static_cast<float>((double)R_FULL_ACCESS - lightElementsAccessPen), 2);
			ret.second = R_FULL_ACCESS;
		}
		else {
			ret.first = R_FULL_ACCESS;
			ret.second = Calc::roundToDecimalPlace<float>(R_FULL_ACCESS - static_cast<float>(bdensity / 1000.0), 2);
		}

		return ret;
	}

	void generateResources()
	{};
};

using CelestialBodyPtr = std::unique_ptr<CelestialBody>;