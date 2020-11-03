#pragma once

#include <qdatetime>
#include <iostream>

#include "GameWindow.h"
#include "Universe.h"
#include "GameSaver.h"

class Engine : public QObject
{
	Q_OBJECT;
		
public:
	Engine(QWidget * mainWindow, QString gameName);
	Engine(QWidget * mainWindow, QString gameName, Universe universe, QDateTime time);
	~Engine();

private:
	QString gameName;
	QDateTime gameTime;
	Universe gameUniverse;
	GameWindow window;

	void changeTime(TimeChange change = TimeChange::hour_1);

	void init();

public slots:
	void showBodyInfo(QTreeWidgetItem * item, int column);
};