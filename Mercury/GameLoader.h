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
	~GameLoader() = default;

	std::vector<ColonyData> loadColonies()
	{
		std::vector<ColonyData> ret;
		QSqlQuery load(getColoniesTable().getSelectQueryStr(), save);
		load.setForwardOnly(true);
		load.exec();

		auto stockTable = getStockTable();
		auto indTable = getIndustryBldgsTable();
		auto constrListTable = getIndustryConstrListTable();
		while (load.next())
		{
			auto colonyID = load.value(0).toUInt();
			auto systemID = load.value(1).toUInt();
			auto bodyID = load.value(2).toUInt();

			stockTable.setNamePostfix({ static_cast<size_t>(colonyID) });
			indTable.setNamePostfix(stockTable.getNamePostfix());
			constrListTable.setNamePostfix(stockTable.getNamePostfix());

			ret.emplace_back(std::make_tuple(std::make_pair(systemID, bodyID), loadStock(stockTable),
				loadIndustryBuildings(indTable), loadConstrList(constrListTable)));
		}
		return ret;
	}

	Universe loadUniverse()
	{
		Universe universe;
		QSqlQuery loadBodies(getCelestialBodiesTable().getSelectQueryStr(), save);
		loadBodies.setForwardOnly(true);
		loadBodies.exec();

		auto systemsName = loadSystemsName();
		for (const auto & i : systemsName)
		{
			universe.addSystem(i);
		}

		auto bodyResTable = getBodyResTable();
		CelestialBodyFactory factory;
		while (loadBodies.next())
		{
			auto systemID = static_cast<size_t>(loadBodies.value(0).toUInt());
			auto bodyID = static_cast<size_t>(loadBodies.value(1).toUInt());
			auto name = loadBodies.value(2).toString();
			auto type = static_cast<CelestialBodyType>(loadBodies.value(3).toUInt());
			auto parentID = loadBodies.value(4);

			std::optional<Orbit> orb;
			if (!parentID.isNull())
			{
				orb.emplace(Orbit(loadBodies.value(5).toDouble() * units::si::meter,
					loadBodies.value(6).toDouble() * units::si::meter,
					universe.getLastSystem().Bodies[parentID.toUInt()].get()->physics.mass,
					parentID.toUInt()));
			}

			PhysicalProperties prop(loadBodies.value(7).toDouble() * units::si::meter,
				loadBodies.value(8).toDouble() * units::si::kilogram,
				loadBodies.value(9).toInt() * units::si::kelvin);
			ResourceDeposit res;

			if (type == CelestialBodyType::Planet)
			{
				bodyResTable.setNamePostfix({ systemID, bodyID });
				res = loadBodyResources(bodyResTable);
			}

			universe.getLastSystem().Bodies.emplace_back(factory.createBody(prop, orb, name, res));
		}

		universe.constructPlayerFactionCols(loadColonies());

		return universe;
	}

	QDateTime loadGameTime()
	{
		QSqlQuery loadTime(getGameTimeTable().getSelectQueryStr(), save);
		loadTime.exec();

		loadTime.next();
		QDateTime gameTime = QDateTime::fromString(loadTime.value(0).toString(), GAME_TIME_FORMAT);
		return gameTime;
	}
private:
	ResourceDeposit loadBodyResources(const SqlTable & table)
	{
		QSqlQuery loadRes(table.getSelectQueryStr(), save);
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
		QSqlQuery loadNames(getSystemsTable().getSelectQueryStr(), save);
		loadNames.exec();

		while (loadNames.next())
		{
			ret.emplace_back(loadNames.value(1).toString());
		}
		return ret;
	}

	QuantityT loadIndustryBuildings(const SqlTable & table)
	{
		QuantityT ret;

		QSqlQuery load(table.getSelectQueryStr(), save);
		load.setForwardOnly(true);
		load.exec();

		while (load.next())
		{
			ret.push_back(load.value(0).toUInt());
		}
		return ret;
	}
	QuantityT loadStock(const SqlTable & table)
	{
		QuantityT ret;

		QSqlQuery load(table.getSelectQueryStr(), save);
		load.setForwardOnly(true);
		load.exec();

		while (load.next())
		{
			ret.push_back(load.value(0).toUInt());
		}
		return ret;
	}
	std::list<Construction> loadConstrList(const SqlTable& table)
	{
		auto ret = std::list<Construction>();

		QSqlQuery load(table.getSelectQueryStr(), save);
		load.exec();

		while (load.next())
		{
			ret.emplace_back(Construction(static_cast<size_t>(load.value(0).toUInt()),
				load.value(2).toInt(), 0, load.value(1).toUInt(),
				static_cast<ConstructionStatus>(load.value(3).toInt())));
		}
		return ret;
	}
};