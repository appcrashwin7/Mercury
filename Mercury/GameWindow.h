#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qevent.h>

#include "ui_GameWindow.h"
#include "ColoniesWindow.h"
#include "SystemRender.h"

enum class TimeChange
{
	hour_1,
	hour_6,
	hour_12,
	hour_24,
	day_7,
	day_30,
	month_6,
	month_12,
	month_24
};


class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow() = delete;
	GameWindow(std::vector<Colony> & cls, QWidget * main);
	~GameWindow() = default;
	void closeEvent(QCloseEvent * event);

	void putTime(const QDateTime * tm);
	void setSystemToRender(const PlanetarySystem * system);

public slots:
	

private:
	Ui::GameWindow ui;
	ColoniesWindow colsWindow;
};