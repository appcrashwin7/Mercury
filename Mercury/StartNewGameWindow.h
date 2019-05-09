#pragma once

#include <QtWidgets/QWidget.h>
#include "ui_NewGameWindow.h"

class StartNewGameWindow : public QWidget
{
	Q_OBJECT


public:
	StartNewGameWindow()
		:QWidget(nullptr)
	{
		ui.setupUi(this);
	}
	~StartNewGameWindow() = default;

private:
	Ui::NewGameWindow ui;
};