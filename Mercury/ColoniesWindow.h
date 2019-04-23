#pragma once

#include <vector>
#include <QtWidgets/qwidget.h>
#include "ui_ColoniesWindow.h"

#include "Colony.h"


class ColoniesWindow : public QWidget
{
	Q_OBJECT


	
public:
	ColoniesWindow() = delete;
	ColoniesWindow(std::vector<Colony> & cl);
	~ColoniesWindow() = default;

private:
	Ui::ColonyWidget ui;
	std::vector<Colony> & colonies;
};