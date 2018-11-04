#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qevent.h>
#include "ui_GameWindow.h"


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
	GameWindow(QWidget * main);
	~GameWindow();
	void closeEvent(QCloseEvent * event);

public slots:
	

private:
	Ui::GameWindow ui;
};