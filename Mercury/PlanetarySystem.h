#pragma once

#include "CelestialBodyFactory.h"

class PlanetarySystem
{
	QString name;
public:
	PlanetarySystem() = delete;
	PlanetarySystem(QString sysName);
	PlanetarySystem(const PlanetarySystem & other) = delete;
	PlanetarySystem(PlanetarySystem && system) = default;
	~PlanetarySystem() = default;
	
	std::vector<CelestialBodyPtr> Bodies;

	void setName(QString newName)
	{
		name = std::move(newName);
	}
	const QString & getName() const
	{
		return name;
	}
};