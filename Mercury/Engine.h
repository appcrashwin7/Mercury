#pragma once

#include <qdatetime>
#include <iostream>

#include "GameWindow.h"
#include "Universe.h"
#include "Colony.h"
#include "GameSaver.h"

class Engine : public QObject
{
	Q_OBJECT;
		
public:
	Engine(QWidget * mainWindow, QString gameName);
	Engine(QWidget * mainWindow, QString gameName, Universe universe, std::vector<ColonyData> dt, QDateTime time);
	~Engine();

private:
	QString gameName;
	QDateTime gameTime;
	Universe gameUniverse;
	std::vector<Colony> Colonies;
	GameWindow window;

	void changeTime(TimeChange change = TimeChange::hour_1);
	const CelestialBody * searchBodyByName(const PlanetarySystem & system, const QString & name);

	void init();

	std::vector<Colony> constructColonies(std::vector<ColonyData> data);

public slots:
	void showBodyInfo(QTreeWidgetItem * item, int column);
};