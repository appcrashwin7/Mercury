#pragma once

#include "MercurySave.h"

class GameSaver : public MercurySave
{
	const Universe * universeToSave = nullptr;
	const std::vector<Colony> * coloniesToSave = nullptr;
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

	void operator()()
	{
		checkIfNullptr(universeToSave);
		checkIfNullptr(coloniesToSave);

		openDB();
		createTables();
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
			"ORBIT_PERIAPSIS real NOT NULL, RADIUS real NOT NULL, MASS real NOT NULL);", save);
		createCelBodiesTable.exec();
		QSqlQuery createColoniesTable("CREATE TABLE IF NOT EXISTS COLONIES("\
			"ID int NOT NULL, SYSTEM_ID int NOT NULL, BODY_ID int NOT NULL);", save);
		createColoniesTable.exec();

	}

	void saveSystems()
	{
		QSqlQuery del("DELETE FROM SYSTEM", save);
		del.exec();
		for (size_t i = 0; i < universeToSave->getSystems().size(); i++)
		{
			QSqlQuery insert("INSERT INTO SYSTEM VALUES (" + QString::number(i) + "," + "'" +
				QString::fromStdString(universeToSave->getSystems()[i].name) + "'" +");", save);
			insert.exec();
		}
	}
	void saveBodies()
	{
		QSqlQuery del("DELETE FROM CELESTIAL_BODIES", save);
		del.exec();
		
		for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
		{
			for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
			{
				auto body = universeToSave->getSystems()[iSys].Bodies[iBody];
				QSqlQuery insertBody;
				insertBody.prepare("INSERT INTO CELESTIAL_BODIES(SYSTEM_ID, ID, NAME, TYPE, PARENT_ID, ORBIT_APOAPSIS, ORBIT_PERIAPSIS, RADIUS, MASS) "
					"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

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
					insertBody.addBindValue(QVariant());
				}

				insertBody.addBindValue(body->bodyOrbit.apoapsis.value());
				insertBody.addBindValue(body->bodyOrbit.periapsis.value());
				insertBody.addBindValue(body->radius.value());
				insertBody.addBindValue(body->mass.value());

				insertBody.exec();
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
					if (universeToSave->getSystems()[iSys].Bodies[iBody] == searched)
					{
						ret.emplace(std::make_pair(iSys, iBody));
					}
				}
			}
			return ret;
		};

		QString createStockTableBeg("CREATE TABLE IF NOT EXISTS STOCK_");
		QString createStockTableEnd("(amount TEXT NOT NULL);");
		QString clearStockTable("DELETE FROM STOCK_");

		QString createIndustryTableBeg("CREATE TABLE IF NOT EXISTS INDUSTRY_");
		QString createIndustryTableEnd("(amount TEXT NOT NULL);");
		QString clearIndustryTable("DELETE FROM INDUSTRY_");

		for (size_t iCol = 0; iCol < coloniesToSave->size(); iCol++)
		{
			QSqlQuery insertCols;
			insertCols.prepare("INSERT INTO COLONIES(ID, SYSTEM_ID, BODY_ID)"
				"VALUES (?, ?, ?);");

			auto iColStr = QString::number(iCol);
			auto planetID = findPlanet(&(coloniesToSave->operator[](iCol).getPlanet()));
			insertCols.addBindValue(iCol);
			insertCols.addBindValue(planetID.value().first);
			insertCols.addBindValue(planetID.value().second);

			insertCols.exec();
			QSqlQuery createStock(createStockTableBeg + iColStr + createStockTableEnd);
			createStock.exec();
			QSqlQuery createIndustry(createIndustryTableBeg + iColStr + createIndustryTableEnd);
			createIndustry.exec();

			QSqlQuery clearStock(clearStockTable + iColStr);
			clearStock.exec();
			QSqlQuery clearIndustry(clearIndustryTable + iColStr);
			clearIndustry.exec();

			QSqlQuery insertStock;
			insertStock.prepare("INSERT INTO STOCK_" + iColStr + "(amount)" + "VALUES(?)");
			QVariantList amountList;
			for (auto & iStock : coloniesToSave->operator[](iCol).getStockpile())
			{
				amountList << QString::number(iStock.second);
			}
			insertStock.addBindValue(amountList);
			insertStock.execBatch();
			
			amountList.clear();
			QSqlQuery insertIndustry;
			insertIndustry.prepare("INSERT INTO INDUSTRY_" + iColStr + "(amount)" + "VALUES(?)");
			for (auto & buildingAm : coloniesToSave->operator[](iCol).getIndustry().getBuildings())
			{
				amountList << QString::number(buildingAm.second);
			}
			insertIndustry.addBindValue(amountList);
			insertIndustry.execBatch();
		}
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