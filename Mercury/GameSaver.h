#pragma once

#include "MercurySave.h"

class GameSaver : public MercurySave
{
	const Universe * universeToSave = nullptr;
	const QDateTime * gameTime = nullptr;
public:
	GameSaver() = delete;
	GameSaver(const QString & fileName)
		:MercurySave(fileName)
	{
	}
	GameSaver(const GameSaver & other) = delete;
	GameSaver(GameSaver &&) = delete;
	~GameSaver() = default;

	void addUniverse(const Universe * universe)
	{
		checkIfNullptr(universe);
		universeToSave = universe;
	}
	void addGameTime(const QDateTime * time)
	{
		checkIfNullptr(time);
		gameTime = time;
	}

	void operator()()
	{
		checkIfNullptr(universeToSave);
		checkIfNullptr(gameTime);

		openDB();
		saveTime();
		saveSystems();
		saveBodies();
		saveColonies();
		closeDB();
	}
private:
	void saveSystems()
	{
		QSqlQuery create(getSystemsTable().getCreateQueryStr());
		create.exec();

		QSqlQuery del(getSystemsTable().getDeleteQueryStr(), save);
		del.exec();

		QSqlQuery insert(save);
		insert.prepare(getSystemsTable().getInsertQueryStr());

		QVariantList idsList;
		QVariantList namesList;

		for (size_t i = 0; i < universeToSave->getSystems().size(); i++)
		{
			idsList << i;
			namesList << universeToSave->getSystems()[i].getName();
		}
		insert.addBindValue(idsList);
		insert.addBindValue(namesList);

		insert.execBatch();
	}
	void saveBodies()
	{
		QSqlQuery createQuery(getCelestialBodiesTable().getCreateQueryStr());
		createQuery.exec();

		QSqlQuery del(getCelestialBodiesTable().getDeleteQueryStr(), save);
		del.exec();

		QSqlQuery insertBody(save);
		insertBody.prepare(getCelestialBodiesTable().getInsertQueryStr());
		std::array<QVariantList, 10> dataForInsert;

		for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
		{
			for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
			{
				auto body = universeToSave->getSystems()[iSys].Bodies[iBody].get();

				dataForInsert[0] << iSys;
				dataForInsert[1] << iBody;
				dataForInsert[2] << body->getName();
				dataForInsert[3] << static_cast<uint32_t>(body->type);

				if (body->orbit.parent.has_value())
				{
					dataForInsert[4] << body->orbit.parent.value();
				}
				else
				{
					dataForInsert[4] << QVariant(QVariant::UInt);
				}

				dataForInsert[5] << body->orbit.apoapsis.value();
				dataForInsert[6] << body->orbit.periapsis.value();
				dataForInsert[7] << body->physics.radius.value();
				dataForInsert[8] << body->physics.mass.value();
				dataForInsert[9] << body->physics.getSurfaceTemperature().value();
				
				saveBodyResources(iSys, iBody, body);
			}
		}

		for (size_t i = 0; i < dataForInsert.size(); i++)
			insertBody.addBindValue(dataForInsert[i]);

		insertBody.execBatch();
	}
	void saveColonies()
	{
		auto findPlanet = [&](const RockyBody * searched)->std::optional<std::pair<size_t, size_t>>
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

		QSqlQuery createColoniesTable("CREATE TABLE IF NOT EXISTS COLONIES("\
			"ID int NOT NULL, SYSTEM_ID int NOT NULL, BODY_ID int NOT NULL);", save);
		createColoniesTable.exec();

		QSqlQuery deleteColonies("DELETE FROM COLONIES", save);
		deleteColonies.exec();

		QSqlQuery insertCols(save);
		insertCols.prepare("INSERT INTO COLONIES(ID, SYSTEM_ID, BODY_ID)"
			"VALUES (?, ?, ?);");
		std::array<QVariantList, 3> data;

		auto& coloniesToSave = universeToSave->getPlayerFaction().getColonies();
		for (size_t iCol = 0; iCol < coloniesToSave.size(); iCol++)
		{
			auto iColStr = QString::number(iCol);
			auto planetID = findPlanet(&(coloniesToSave[iCol].getBody()));

			data[0] << iCol;
			data[1] << planetID.value().first;
			data[2] << planetID.value().second;
			
			saveStock(coloniesToSave[iCol].getStockpile(), iColStr);
			saveIndustry(coloniesToSave[iCol].getIndustry(), iColStr);
		}
		for (size_t i = 0; i < data.size(); i++)
			insertCols.addBindValue(data[i]);

		insertCols.execBatch();
	}

	void saveStock(const StockT & stock, const QString & colonyIDStr)
	{
		QSqlQuery createStock("CREATE TABLE IF NOT EXISTS STOCK_" + colonyIDStr +
			"(AMOUNT text NOT NULL);", save);
		createStock.exec();
		QSqlQuery clearStock("DELETE FROM STOCK_" + colonyIDStr);
		clearStock.exec();

		QSqlQuery insertStock(save);
		insertStock.prepare("INSERT INTO STOCK_" + colonyIDStr + "(AMOUNT)" + "VALUES(?)");

		QVariantList amountList;
		for (const auto & iStock : stock)
			amountList << QString::number(iStock.second);

		insertStock.addBindValue(amountList);
		insertStock.execBatch();
	}
	void saveIndustry(const Industry & ind, const QString & colonyIDStr)
	{
		QSqlQuery createIndustry("CREATE TABLE IF NOT EXISTS INDUSTRY_"
			+ colonyIDStr + "(AMOUNT text NOT NULL);", save);
		createIndustry.exec();
		QSqlQuery clearIndustry("DELETE FROM INDUSTRY_" + colonyIDStr, save);
		clearIndustry.exec();

		QSqlQuery insertIndustry(save);
		insertIndustry.prepare("INSERT INTO INDUSTRY_" + colonyIDStr + "(AMOUNT)" + "VALUES(?)");

		QVariantList amountList;
		for (auto & buildingAm : ind.getBuildings())
			amountList << QString::number(buildingAm.second);

		insertIndustry.addBindValue(amountList);
		insertIndustry.execBatch();
	}

	void saveTime()
	{
		QSqlQuery timeTableCreate(getGameTimeTable().getCreateQueryStr(), save);
		timeTableCreate.exec();

		QSqlQuery timeDel(getGameTimeTable().getDeleteQueryStr(), save);
		timeDel.exec();

		QSqlQuery timeInsert(save);
		timeInsert.prepare(getGameTimeTable().getInsertQueryStr());
		timeInsert.addBindValue(gameTime->toString(GAME_TIME_FORMAT));
		timeInsert.exec();
	}

	void saveBodyResources(size_t iSystem, size_t iBody, const CelestialBody * body)
	{
		const RockyBody * rockyBody = dynamic_cast<const RockyBody*>(body);
		if (rockyBody == nullptr)
			return;

		QString iBodyStr = QString::number(iBody);
		QString iSysStr = QString::number(iSystem);

		QSqlQuery resourceTableCr("CREATE TABLE IF NOT EXISTS RESOURCES_" + iSysStr + "_" 
			+ iBodyStr + "( AMOUNT TEXT NOT NULL, ACCESS real NOT NULL);", save);
		resourceTableCr.exec();

		QString resourceTableDel("DELETE FROM RESOURCES_");
		QSqlQuery resourcesTableDel(resourceTableDel + iSysStr + "_" + iBodyStr, save);
		resourcesTableDel.exec();

		QSqlQuery saveResources(save);
		saveResources.prepare("INSERT INTO RESOURCES_" + iSysStr + 
			"_" + iBodyStr + "(AMOUNT, ACCESS) VALUES(?, ?)");

		QVariantList resAmountToSave;
		QVariantList resAccessToSave;

		auto & Res = rockyBody->getResources();
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