#pragma once

#include "MercurySave.h"

class GameLoader : public MercurySave
{

public:
	GameLoader() = delete;
	GameLoader(const GameLoader & other) = delete;
	GameLoader(GameLoader && other) = default;
	GameLoader(const QString & fileName)
		:MercurySave(fileName)
	{
		openDB();
	}
	~GameLoader()
	{
		closeDB();
	}

	std::vector<ColonyData> loadColonies()
	{
		std::vector<ColonyData> ret;
		QSqlQuery load("SELECT ID, SYSTEM_ID, BODY_ID FROM COLONIES", save);
		load.setForwardOnly(true);
		load.exec();

		while (load.next())
		{
			auto colonyID = load.value(0).toUInt();
			auto systemID = load.value(1).toUInt();
			auto bodyID = load.value(2).toUInt();

			QString colonyIDStr = QString::number(colonyID);

			ret.emplace_back(std::make_tuple(std::make_pair(systemID, bodyID), loadStock(colonyIDStr), loadIndustryBuildings(colonyIDStr)));
		}
		return ret;
	}

	Universe loadUniverse()
	{
		Universe universe;
		QSqlQuery loadBodies("SELECT SYSTEM_ID, ID, NAME, TYPE, PARENT_ID, " \
			"ORBIT_APOAPSIS, ORBIT_PERIAPSIS, RADIUS, MASS, TEMPERATURE FROM CELESTIAL_BODIES", save);
		loadBodies.setForwardOnly(true);
		loadBodies.exec();

		auto systemsName = loadSystemsName();
		for (const auto & i : systemsName)
		{
			universe.addSystem(i.toStdString());
		}

		while (loadBodies.nextResult())
		{
			auto systemID = loadBodies.value(0).toUInt();
			auto bodyID = loadBodies.value(1).toUInt();
			auto name = loadBodies.value(2).toString();
			auto type = static_cast<CelestialBodyType>(loadBodies.value(3).toUInt());
			auto parentID = loadBodies.value(4);
			auto apoapsis = loadBodies.value(5).toDouble();
			auto periapsis = loadBodies.value(6).toDouble();
			auto radius = loadBodies.value(7).toDouble();
			auto mass = loadBodies.value(8).toDouble();
			auto temperature = loadBodies.value(9).toInt();


			CelestialBodyPtr body;
			std::optional<size_t> parent;
			std::optional<Mass> parentMass;
			if (!parentID.isNull())
			{
				parent = parentID.toUInt();
				parentMass = universe.getLastSystem().Bodies[parent.value()].get()->physics.mass;
			}
			body = std::move(CelestialBodyPtr(new CelestialBody(
				PhysicalProperties(radius * units::si::meter, mass * units::si::kilogram, temperature * units::si::kelvin),
				type, Orbit(apoapsis * units::si::meter, periapsis * units::si::meter, parentMass, parent), name)));


			switch (type)
			{
			case CelestialBodyType::Star:
				universe.getSystem(systemID).Bodies.emplace_back(std::move(CelestialBodyPtr(new Star(*body))));
				break;
			case CelestialBodyType::Planet:
				universe.getSystem(systemID).Bodies.emplace_back(std::move(CelestialBodyPtr(new Planet(*body, loadBodyResources(systemID, bodyID)))));
				break;
			case CelestialBodyType::GasGiant:
				break;
			case CelestialBodyType::Asteroid:
				break;
			}
		}
		return universe;
	}

	QDateTime loadGameTime()
	{
		QSqlQuery loadTime("SELECT TIME FROM GAME_TIME", save);
		loadTime.exec();

		loadTime.next();
		QDateTime gameTime = QDateTime::fromString(loadTime.value(0).toString(), GAME_TIME_FORMAT);
		return gameTime;
	}
private:
	ResourceDeposit loadBodyResources(size_t iSystem, size_t iBody)
	{
		QSqlQuery loadRes("SELECT AMOUNT, ACCESS FROM RESOURCES_" + QString::number(iSystem) + "_" + QString::number(iBody), save);
		loadRes.exec();
		ResourceDeposit res;

		for (size_t iRes = 0; iRes < RESOURCES_LIST_SIZE; iRes++)
		{
			loadRes.next();
			res.editDeposit(iRes) = std::make_pair<uint64_t, float>(loadRes.value(0).toUInt(), loadRes.value(1).toFloat());
		}
		return res;
	}

	std::vector<QString> loadSystemsName()
	{
		std::vector<QString> ret;
		QSqlQuery loadNames("SELECT ID, NAME FROM SYSTEMS", save);
		loadNames.exec();

		while (loadNames.next())
		{
			ret.emplace_back(loadNames.value(1).toString());
		}
		return ret;
	}

	QuantityT loadIndustryBuildings(const QString & colonyIDStr)
	{
		QuantityT ret;

		QSqlQuery load("SELECT AMOUNT FROM INDUSTRY_" + colonyIDStr, save);
		load.setForwardOnly(true);
		load.exec();

		while (load.next())
		{
			ret.push_back(load.value(0).toUInt());
		}
		return ret;
	}
	QuantityT loadStock(const QString & colonyIDStr)
	{
		QuantityT ret;

		QSqlQuery load("SELECT AMOUNT FROM STOCK_" + colonyIDStr, save);
		load.setForwardOnly(true);
		load.exec();

		while (load.next())
		{
			ret.push_back(load.value(0).toUInt());
		}
		return ret;
	}
};