#pragma once

#include <vector>
#include <QtWidgets/qwidget.h>
#include "ui_ColoniesWindow.h"

#include "Colony.h"


class ColoniesWindow : public QWidget
{
	Q_OBJECT


	int selectedColony;
public:
	ColoniesWindow() = delete;
	ColoniesWindow(std::vector<Colony> & cl);
	~ColoniesWindow() = default;

public slots:
	void resetData();

private:
	Ui::ColonyWidget ui;
	std::vector<Colony> & colonies;
};