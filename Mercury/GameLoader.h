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


	Universe && loadUniverse()
	{
		Universe universe;
		QSqlQuery loadBodies("SELECT SYSTEM_ID, ID, NAME, TYPE, PARENT_ID, " \
			"ORBIT_APOAPSIS, ORBIT_PERIAPSIS, RADIUS, MASS, TEMPERATURE FROM CELESTIAL_BODIES");
		loadBodies.exec();

		auto systems = loadSystemsName();
		for (const auto & i : systems)
		{
			universe.addSystem(i.toStdString());
		}

		while (loadBodies.next())
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

			
			CelestialBodyPtr body(new CelestialBody(radius * units::si::meter, mass * units::si::kilogram, type, std::make_optional(parentID.toUInt()),
				Orbit(apoapsis * units::si::meter, periapsis * units::si::meter), name.toStdString(), temperature * units::si::kelvin));
			if (parentID.isNull())
			{
				body = std::move(CelestialBodyPtr(new CelestialBody(radius * units::si::meter, mass * units::si::kilogram, type, std::optional<size_t>(),
					Orbit(apoapsis * units::si::meter, periapsis * units::si::meter), name.toStdString(), temperature * units::si::kelvin)));
			}

			switch (type)
			{
			case CelestialBodyType::Undefided:
				break;
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
			default:
				break;
			}
		}
		return std::move(universe);
	}

	QDateTime loadGameTime()
	{
		QSqlQuery loadTime("SELECT TIME FROM GAME_TIME");
		loadTime.exec();

		loadTime.next();
		QDateTime gameTime;
		gameTime.fromString(loadTime.value(0).toString(), GAME_TIME_FORMAT);
		return gameTime;
	}
private:
	ResourceDeposit && loadBodyResources(size_t iSystem, size_t iBody)
	{
		QSqlQuery loadRes("SELECT AMOUNT, ACCESS FROM RESOURCES_" + QString::number(iSystem) + "_" + QString::number(iBody));
		loadRes.exec();
		ResourceDeposit res;

		for (size_t iRes = 0; iRes < RESOURCES_LIST_SIZE; iRes++)
		{
			loadRes.next();
			res.editDeposit(iRes) = std::make_pair<uint64_t, float>(loadRes.value(0).toUInt(), loadRes.value(1).toFloat());
		}
		return std::move(res);
	}

	std::vector<QString> loadSystemsName()
	{
		std::vector<QString> ret;
		QSqlQuery loadNames("SELECT ID, NAME FROM SYSTEMS");
		loadNames.exec();

		while (loadNames.next())
		{
			ret.emplace_back(loadNames.value(1).toString());
		}
		return ret;
	}

	Industry && loadIndustry(size_t colonyID)
	{
		Industry ret;
		std::vector<uint64_t> amount;
		QSqlQuery load("SELECT AMOUNT FROM INDUSTRY_" + QString::number(colonyID));
		load.exec();

		while (load.next())
		{
			amount.push_back(load.value(0).toUInt());
		}
		ret += (amount);
		return std::move(ret);
	}
	StockT && loadStock(size_t colonyID)
	{
		QSqlQuery load("SELECT AMOUNT FROM STOCK_" + QString::number(colonyID));
		load.exec();

		StockT ret;
		Commodities commd;

		for (size_t i = 0; i < commd.get().size(); i++)
		{
			load.next();
			ret.emplace_back(StockUnit(commd.get()[i], load.value(0).toUInt()));
		}
		return std::move(ret);
	}
};