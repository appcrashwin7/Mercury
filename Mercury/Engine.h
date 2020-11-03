#pragma once

#include <qdatetime>

#include "GameWindow.h"
#include "Universe.h"
#include "GameSaver.h"

class Engine : public QObject
{
	Q_OBJECT;
		
	QString gameName;
	QDateTime gameTime;
	Universe gameUniverse;
	GameWindow window;
public:
	Engine(QWidget * mainWindow, QString gameName);
	Engine(QWidget * mainWindow, QString gameName, Universe universe, QDateTime time);
	~Engine();

private:
	void init();

	void changeTime(TimeChange change = TimeChange::hour_1);
	void showBodyInfo(size_t bodyID);
};