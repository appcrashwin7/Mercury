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
		auto bodyResTable = getBodyResTable();

		for (size_t iSys = 0; iSys < universeToSave->getSystems().size(); iSys++)
		{
			for (size_t iBody = 0; iBody < universeToSave->getSystems()[iSys].Bodies.size(); iBody++)
			{
				auto body = universeToSave->getSystems()[iSys].Bodies[iBody].get();

				dataForInsert[0] << iSys;
				dataForInsert[1] << iBody;
				dataForInsert[2] << body->getName();
				dataForInsert[3] << static_cast<uint32_t>(body->type);
				dataForInsert[4] << (body->orbit ? body->orbit->parent : QVariant());
				dataForInsert[5] << (body->orbit ? body->orbit->apoapsis.value() : QVariant());
				dataForInsert[6] << (body->orbit ? body->orbit->periapsis.value() : QVariant());
				dataForInsert[7] << body->physics.radius.value();
				dataForInsert[8] << body->physics.mass.value();
				dataForInsert[9] << body->physics.getSurfaceTemperature().value();
				
				if (body->type == CelestialBodyType::Planet)
				{
					bodyResTable.setNamePostfix({ iSys, iBody });
					saveBodyResources(bodyResTable, dynamic_cast<RockyBody*>(body));
				}	
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

		QSqlQuery createColoniesTable(getColoniesTable().getCreateQueryStr() , save);
		createColoniesTable.exec();

		QSqlQuery deleteColonies(getColoniesTable().getDeleteQueryStr(), save);
		deleteColonies.exec();

		QSqlQuery insertCols(save);
		insertCols.prepare(getColoniesTable().getInsertQueryStr());
		std::array<QVariantList, 3> data;

		auto& coloniesToSave = universeToSave->getPlayerFaction().getColonies();
		auto stockTable = getStockTable();
		auto indTable = getIndustryBldgsTable();
		auto constrList = getIndustryConstrListTable();
		for (size_t iCol = 0; iCol < coloniesToSave.size(); iCol++)
		{
			auto planetID = findPlanet(&(coloniesToSave[iCol].getBody()));

			data[0] << iCol;
			data[1] << planetID.value().first;
			data[2] << planetID.value().second;
			
			stockTable.setNamePostfix({ iCol });
			indTable.setNamePostfix(stockTable.getNamePostfix());
			constrList.setNamePostfix(indTable.getNamePostfix());

			saveStock(coloniesToSave[iCol].getStockpile(), stockTable);
			saveIndustry(coloniesToSave[iCol].getIndustry(), indTable);
			saveConstructionList(coloniesToSave[iCol].getConstructionQueue(), constrList);
		}
		for (size_t i = 0; i < data.size(); i++)
			insertCols.addBindValue(data[i]);

		insertCols.execBatch();
	}

	void saveStock(const StockT & stock, const SqlTable& table)
	{
		QSqlQuery createStock(table.getCreateQueryStr(), save);
		createStock.exec();
		QSqlQuery clearStock(table.getDeleteQueryStr());
		clearStock.exec();

		QSqlQuery insertStock(save);
		insertStock.prepare(table.getInsertQueryStr());

		QVariantList amountList;
		for (const auto & iStock : stock)
			amountList << QString::number(iStock.second);

		insertStock.addBindValue(amountList);
		insertStock.execBatch();
	}
	void saveIndustry(const Industry & ind, const SqlTable & table)
	{
		QSqlQuery createIndustry(table.getCreateQueryStr(), save);
		createIndustry.exec();
		QSqlQuery clearIndustry(table.getDeleteQueryStr(), save);
		clearIndustry.exec();

		QSqlQuery insertIndustry(save);
		insertIndustry.prepare(table.getInsertQueryStr());

		QVariantList amountList;
		for (auto & buildingAm : ind.getBuildings())
			amountList << QString::number(buildingAm.second);

		insertIndustry.addBindValue(amountList);
		insertIndustry.execBatch();
	}
	void saveConstructionList(const std::list<Construction>& list, const SqlTable& table)
	{
		QSqlQuery create(table.getCreateQueryStr(), save);
		create.exec();
		QSqlQuery clear(table.getDeleteQueryStr(), save);
		clear.exec();

		QSqlQuery insert(table.getInsertQueryStr(), save);
		std::vector<QVariantList> dt(table.getTableVariables().size(), QVariantList());
		for (auto& l : list)
		{
			dt[0] << l.getBuildingID();
			dt[1] << l.getConstructionCost();
			dt[2] << l.getAmount();
			dt[3] << static_cast<int>(l.getStatus());
		}
		for (const auto& t : dt)
			insert.addBindValue(t);

		insert.execBatch();
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

	void saveBodyResources(const SqlTable & table, const RockyBody * body)
	{
		QSqlQuery resourceTableCr(table.getCreateQueryStr(), save);
		resourceTableCr.exec();

		QSqlQuery resourcesTableDel(table.getDeleteQueryStr(), save);
		resourcesTableDel.exec();

		QSqlQuery saveResources(save);
		saveResources.prepare(table.getInsertQueryStr());

		QVariantList resAmountToSave;
		QVariantList resAccessToSave;

		auto & Res = body->getResources();
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