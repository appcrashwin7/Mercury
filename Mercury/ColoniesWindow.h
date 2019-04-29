#pragma once

#include <vector>
#include <QtWidgets/qwidget.h>
#include "ui_ColoniesWindow.h"

#include "Colony.h"

enum class TabT
{
	Summary,
	Industry,
	Mining,
	Stockpile
};

class ColoniesWindow : public QWidget
{
	Q_OBJECT


	TabT selectedTab;
	int selectedColony;
public:
	ColoniesWindow() = delete;
	ColoniesWindow(std::vector<Colony> & cl);
	~ColoniesWindow() = default;

public slots:
	void resetData();
	void setSelectedColony(QTreeWidgetItem * item, int column);

private:
	Ui::ColonyWidget ui;
	std::vector<Colony> & colonies;

	QTreeWidget * getColoniesTree();
};