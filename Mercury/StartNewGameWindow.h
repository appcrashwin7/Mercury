#pragma once

#include <QtWidgets/QWidget.h>
#include "ui_NewGameWindow.h"

class StartNewGameWindow : public QWidget
{
	Q_OBJECT


public:
	StartNewGameWindow(QWidget * parent);
	~StartNewGameWindow();

private:
	Ui::NewGameWindow ui;
};