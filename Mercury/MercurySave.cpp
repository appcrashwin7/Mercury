#include "MercurySave.h"


MercurySave::MercurySave(const QString& fileName)
	:fileName(fileName)
{}
MercurySave::~MercurySave()
{
	closeDB();
}

void MercurySave::openDB()
{
	QFile file(fileName);
	if (file.exists())
	{
		file.close();
		QFile::rename(fileName, getDbFileName());
	}
	save.setDatabaseName(getDbFileName());
	save.open();
}
void MercurySave::closeDB()
{
	save.close();
	if (fileName.isEmpty())
		return;

	QFile::rename(getDbFileName(), fileName);
}

SqlTable MercurySave::getGameTimeTable()
{
	return SqlTable("GAME_TIME",
		{ {"TIME", "text", true} });
}
SqlTable MercurySave::getSystemsTable()
{
	return SqlTable("SYSTEMS",
		{ {"ID", "int", true},
		 {"NAME", "text", false} });
}
SqlTable MercurySave::getCelestialBodiesTable()
{
	return SqlTable("CELESTIAL_BODIES",
		{ {"SYSTEM_ID", "int", true},
		{"ID", "int", true},
		{"NAME", "text", false},
		{"TYPE", "int", true},
		{"PARENT_ID", "int", false},
		{"ORBIT_APOAPSIS", "real", false},
		{"ORBIT_PERIAPSIS", "real", false},
		{"RADIUS", "real", true},
		{"MASS", "real", true},
		{"TEMPERATURE", "int", true}
		});
}
SqlTable MercurySave::getColoniesTable()
{
	return SqlTable("COLONIES",
		{ {"ID", "int", true},
		{"SYSTEM_ID", "int", true},
		{"BODY_ID", "int", true}
		});
}
SqlTable MercurySave::getStockTable()
{
	return SqlTable("STOCK",
		{ {"AMOUNT", "int", true} });
}
SqlTable MercurySave::getIndustryBldgsTable()
{
	return SqlTable("INDUSTRY",
		{ {"AMOUNT", "int", true} });
}
SqlTable MercurySave::getBodyResTable()
{
	return SqlTable("RESOURCES",
		{ {"AMOUNT", "text", true},
		{"ACCESS", "real", true} });
}

QString MercurySave::getDbFileName() const
{
	auto dbNameStr = fileName.toStdString();
	dbNameStr = dbNameStr.substr(0, dbNameStr.find_last_of('.'));
	return QString::fromStdString(dbNameStr) + DB_EXTENSION;
}