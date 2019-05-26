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
};