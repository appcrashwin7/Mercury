#pragma once

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qevent.h>
#include "ui_GameWindow.h"


class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(QWidget * main);
	~GameWindow();
	void closeEvent(QCloseEvent * event);

private:
	Ui::GameWindow ui;
};