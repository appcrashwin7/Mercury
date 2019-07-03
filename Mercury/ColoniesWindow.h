#pragma once

#include <vector>
#include <QtWidgets/qwidget.h>

#include "ui_ColoniesWindow.h"
#include "ui_StockpileWindow.h"
#include "ui_MiningWindow.h"
#include "ui_SummaryWindow.h"
#include "ui_IndustryWindow.h" 

#include "Colony.h"
#include "Utils.h"

enum class TabT
{
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
	std::vector<Colony> & colonies;

	Ui::ColonyWidget ui;
	Ui::StockWindow uiStock;
	Ui::MiningWindow uiMining;
	Ui::SummaryWindow uiSummary;
	Ui::IndustryWindow uiIndustry;

	QWidget stock;
	QWidget mining;
	QWidget summary;
	QWidget industry;
public:
	ColoniesWindow() = delete;
	ColoniesWindow(std::vector<Colony> & cl);
	~ColoniesWindow() = default;

public slots:
	void resetData();
	void setSelectedColony(QTreeWidgetItem * item, int column);

private:
	void fillStock();
	void fillMining();
	void fillIndustry();
	void fillSummary();
};