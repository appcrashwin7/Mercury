#pragma once

#include "MercurySave.h"

class GameSaver : public MercurySave
{
	const Universe * universeToSave = nullptr;
	const std::vector<Colony> * coloniesToSave = nullptr;
	const QDateTime * gameTime = nullptr;
public:
	GameSaver() = delete;
	GameSaver(const QString & fileName)
		:MercurySave(fileName)
	{
	}
	~GameSaver() = default;

	void addUniverse(const Universe * universe)
	{
		checkIfNullptr(universe);
		universeToSave = universe;
	}
	void addColonies(const std::vector<Colony> * colonies)
	{
		checkIfNullptr(colonies);
		coloniesToSave = colonies;
	}
	void addGameTime(const QDateTime * time)
	{
		checkIfNullptr(time);
		gameTime = time;
	}

	void operator()()
	{
		checkIfNullptr(universeToSave);
		checkIfNullptr(coloniesToSave);
		checkIfNullptr(gameTime);

		openDB();
		createTables();
		saveTime();
		saveSystems();
		saveBodies();
		saveColonies();
		closeDB();
	}
private:
	void createTables()
	{
		QSqlQuery createSystemsTable("CREATE TABLE IF NOT EXISTS SYSTEM(ID int NOT NULL, NAME text);", save);
		createSystemsTable.exec();
		QSqlQuery createCelBodiesTable("CREATE TABLE IF NOT EXISTS CELESTIAL_BODIES(SYSTEM_ID int NOT NULL, " \
			"ID int NOT NULL, NAME text, TYPE int NOT NULL, PARENT_ID int, ORBIT_APOAPSIS real NOT NULL, " \
			"ORBIT_PERIAPSIS real NOT NULL, RADIUS real NOT NULL, MASS real NOT NULL, TEMPERATURE int NOT NULL);", save);
		createCelBodiesTable.exec();
		QSqlQuery createColoniesTable("CREATE TABLE IF NOT EXISTS COLONIES("\
			"ID int NOT NULL, SYSTEM_ID int NOT NULL, BODY_ID int NOT NULL);", save);
		createColoniesTable.exec();
	}

	void saveSystems()
	{
		QSqlQuery del("DELETE FROM SYSTEM", save);
		del.exec();

		QSqlQuery insert(save);
		insert.prepare("INSERT INTO SYSTEM(ID, NAME) VALUES(?, ?)");

		QVariantList idsList;
		QVariantList namesList;

		for (size_t i = 0; i < universeToSave->getSystems().size(); i++)
		{
			idsList << i;
			namesList << QString::fromStdString(universeToSave->getSystems()[i].name);
		}
		insert.addBindValue(idsList);
		insert.addBindValue(namesList);

		insert.execBatch();
	}
	void saveBodies()
	{
		QSqlQuery del("DELETE FROM CELESTIAL_BODIES", save);
		del.exec();

		for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
		{
			for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
			{
				auto body = universeToSave->getSystems()[iSys].Bodies[iBody].get();

				QSqlQuery insertBody(save);
				insertBody.prepare("INSERT INTO CELESTIAL_BODIES(SYSTEM_ID, ID, NAME, TYPE, PARENT_ID, ORBIT_APOAPSIS, ORBIT_PERIAPSIS, RADIUS, MASS, TEMPERATURE) "
					"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

				insertBody.addBindValue(iSys);
				insertBody.addBindValue(iBody);
				insertBody.addBindValue(QString::fromStdString(body->name));
				insertBody.addBindValue(static_cast<uint32_t>(body->type));

				if (body->parent.has_value())
				{
					insertBody.addBindValue(body->parent.value());
				}
				else
				{
					insertBody.addBindValue(QVariant(QVariant::UInt));
				}

				insertBody.addBindValue(body->bodyOrbit.apoapsis.value());
				insertBody.addBindValue(body->bodyOrbit.periapsis.value());
				insertBody.addBindValue(body->radius.value());
				insertBody.addBindValue(body->mass.value());
				insertBody.addBindValue(body->surfaceTemperature.value());

				insertBody.exec();
				saveBodyResources(iSys, iBody, body);
			}
		}
	}
	void saveColonies()
	{
		auto findPlanet = [&](const Planet * searched)->std::optional<std::pair<size_t, size_t>>
		{
			auto ret = std::optional<std::pair<size_t, size_t>>();
			for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
			{
				for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
				{
					if (universeToSave->getSystems()[iSys].Bodies[iBody].get() == searched)
					{
						ret.emplace(std::make_pair(iSys, iBody));
					}
				}
			}
			return ret;
		};

		QString createStockTableBeg("CREATE TABLE IF NOT EXISTS STOCK_");
		QString createStockTableEnd("(AMOUNT text NOT NULL);");
		QString clearStockTable("DELETE FROM STOCK_");

		QString createIndustryTableBeg("CREATE TABLE IF NOT EXISTS INDUSTRY_");
		QString createIndustryTableEnd("(AMOUNT text NOT NULL);");
		QString clearIndustryTable("DELETE FROM INDUSTRY_");

		QSqlQuery deleteColonies("DELETE FROM COLONIES", save);
		deleteColonies.exec();

		for (size_t iCol = 0; iCol < coloniesToSave->size(); iCol++)
		{
			QSqlQuery insertCols(save);
			insertCols.prepare("INSERT INTO COLONIES(ID, SYSTEM_ID, BODY_ID)"
				"VALUES (?, ?, ?);");

			auto iColStr = QString::number(iCol);
			auto planetID = findPlanet(&(coloniesToSave->operator[](iCol).getPlanet()));
			insertCols.addBindValue(iCol);
			insertCols.addBindValue(planetID.value().first);
			insertCols.addBindValue(planetID.value().second);

			insertCols.exec();
			QSqlQuery createStock(createStockTableBeg + iColStr + createStockTableEnd, save);
			createStock.exec();
			QSqlQuery createIndustry(createIndustryTableBeg + iColStr + createIndustryTableEnd, save);
			createIndustry.exec();

			QSqlQuery clearStock(clearStockTable + iColStr);
			clearStock.exec();
			QSqlQuery clearIndustry(clearIndustryTable + iColStr);
			clearIndustry.exec();

			QSqlQuery insertStock(save);
			insertStock.prepare("INSERT INTO STOCK_" + iColStr + "(AMOUNT)" + "VALUES(?)");
			QVariantList amountList;
			for (auto & iStock : coloniesToSave->operator[](iCol).getStockpile())
			{
				amountList << QString::number(iStock.second);
			}
			insertStock.addBindValue(amountList);
			insertStock.execBatch();
			
			amountList.clear();
			QSqlQuery insertIndustry(save);
			insertIndustry.prepare("INSERT INTO INDUSTRY_" + iColStr + "(AMOUNT)" + "VALUES(?)");
			for (auto & buildingAm : coloniesToSave->operator[](iCol).getIndustry().getBuildings())
			{
				amountList << QString::number(buildingAm.second);
			}
			insertIndustry.addBindValue(amountList);
			insertIndustry.execBatch();
		}
	}
	void saveTime()
	{
		QSqlQuery timeTableCreate("CREATE TABLE IF NOT EXISTS GAME_TIME(TIME text NOT NULL);", save);
		timeTableCreate.exec();

		QSqlQuery timeDel("DELETE FROM GAME_TIME", save);
		timeDel.exec();

		QSqlQuery timeInsert(save);
		timeInsert.prepare("INSERT INTO GAME_TIME(TIME) VALUES(?)");
		timeInsert.addBindValue(gameTime->toString(GAME_TIME_FORMAT));
		timeInsert.exec();
	}

	void saveBodyResources(size_t iSystem, size_t iBody, const CelestialBody * body)
	{
		if (body->type == CelestialBodyType::Star || body->type == CelestialBodyType::GasGiant)
			return;

		QString iBodyStr = QString::number(iBody);
		QString iSysStr = QString::number(iSystem);

		QString resourcesTableCrBeg("CREATE TABLE IF NOT EXISTS RESOURCES_");
		QString resourcesTableCrEnd("( AMOUNT TEXT NOT NULL, ACCESS real NOT NULL);");
		QSqlQuery resourceTableCr(resourcesTableCrBeg + iSysStr + "_" + iBodyStr + resourcesTableCrEnd, save);
		resourceTableCr.exec();

		QString resourceTableDel("DELETE FROM RESOURCES_");
		QSqlQuery resourcesTableDel(resourceTableDel + iSysStr + "_" + iBodyStr, save);
		resourcesTableDel.exec();

		QString saveResourcesBeg("INSERT INTO RESOURCES_");
		QString saveResourcesEnd("(AMOUNT, ACCESS) VALUES(?, ?)");
		QSqlQuery saveResources(save);
		saveResources.prepare(saveResourcesBeg + iSysStr + "_" + iBodyStr + saveResourcesEnd);

		QVariantList resAmountToSave;
		QVariantList resAccessToSave;

		auto & Res = body->accessResources();
		for (auto & iRes : Res.get())
		{
			resAmountToSave << QString::number(iRes.first);
			resAccessToSave << iRes.second;
		}

		saveResources.addBindValue(resAmountToSave);
		saveResources.addBindValue(resAccessToSave);
		saveResources.execBatch();
	}

	template<typename T>
	bool checkIfNullptr(T * ptr)
	{
		if (ptr == nullptr)
		{
			qFatal("GameSaver received nullptr!");
		}
		return false;
	}
};