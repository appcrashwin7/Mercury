#pragma once

#include <QtSql/qsqldatabase>
#include <QtSql/qsqlerror>
#include <QtSql/qsqlquery>
#include <qfile>
#include <qvariant>

#include "SqlTable.h"
#include "Universe.h"

const static QString GAME_SAVE_EXTENSION = ".msave";
const static QString DB_EXTENSION = ".db";

const static QString GAME_TIME_FORMAT = "d/M/yyyy h:mm AD";

class MercurySave
{
protected:
	QSqlDatabase save = QSqlDatabase::addDatabase("QSQLITE");
	QString fileName;

public:
	MercurySave() = default;
	MercurySave(const QString& fileName);
	virtual ~MercurySave();

protected:
	void openDB();
	void closeDB();

	static SqlTable getGameTimeTable();
	static SqlTable getSystemsTable();
	static SqlTable getCelestialBodiesTable();
	static SqlTable getColoniesTable();
	static SqlTable getStockTable();
	static SqlTable getIndustryBldgsTable();
	static SqlTable getBodyResTable();

private:
	QString getDbFileName() const;
};