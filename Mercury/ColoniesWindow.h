#pragma once

#include <vector>
#include <QtWidgets/qwidget.h>

#include "ui_ColoniesWindow.h"
#include "ui_StockpileWindow.h"
#include "ui_MiningWindow.h"
#include "ui_SummaryWindow.h"

#include "Colony.h"

enum class TabT
{
	Undefined,
	Summary,
	Industry,
	Mining,
	Stockpile,
	Economy
};

class ColoniesWindow : public QWidget
{
	Q_OBJECT


	TabT selectedTab;
	TabT previousTab;

	std::optional<size_t> selectedColony;

	QWidget stock;
	QWidget mining;
	QWidget summary;
public:
	ColoniesWindow() = delete;
	ColoniesWindow(std::vector<Colony> & cl);
	~ColoniesWindow() = default;

public slots:
	void resetData();
	void setSelectedColony(QTreeWidgetItem * item, int column);

private:
	Ui::ColonyWidget ui;
	Ui::StockWindow uiStock;
	Ui::MiningWindow uiMining;
	Ui::SummaryWindow uiSummary;

	std::vector<Colony> & colonies;

};