#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), previousTab(TabT::Undefined), selectedTab(TabT::Undefined)
{
	ui.setupUi(this);

	QObject::connect(ui.coloniesTree, &QTreeWidget::itemClicked, this, &ColoniesWindow::setSelectedColony);
	QObject::connect(ui.summary, &QPushButton::clicked, [=] {this->selectedTab = TabT::Summary; resetData(); });
	QObject::connect(ui.industry, &QPushButton::clicked, [=] {this->selectedTab = TabT::Industry; resetData(); });
	QObject::connect(ui.mining, &QPushButton::clicked, [=] {this->selectedTab = TabT::Mining; resetData(); });
	QObject::connect(ui.stock, &QPushButton::clicked, [=] {this->selectedTab = TabT::Stockpile; resetData(); });
	QObject::connect(ui.economy, &QPushButton::clicked, [=] {this->selectedTab = TabT::Economy; resetData(); });

	uiMining.setupUi(&mining);
	uiStock.setupUi(&stock);
	uiSummary.setupUi(&summary);
	uiIndustry.setupUi(&industry);

	QObject::connect(uiIndustry.itemTypeSelector, QOverload<const QString &>::of(&QComboBox::activated), 
		[&](const QString & var) {

		if (!selectedColony.has_value())
			return;

		uiIndustry.itemsTable->setRowCount(0);

		if (var == "Buildings")
		{
			for (auto & b : colonies[selectedColony.value()].getIndustry().getBuildings())
			{
				uiIndustry.itemsTable->insertRow(uiIndustry.itemsTable->rowCount());
				uiIndustry.itemsTable->setItem(uiIndustry.itemsTable->rowCount() - 1, 0, 
					new QTableWidgetItem(QString::fromStdString(b.first.getName())));
			}
		}
	});
	QObject::connect(uiIndustry.itemsTable, &QTableWidget::cellClicked, [&](int row, int column)
	{
		column;
		uiIndustry.itemCostTable->setRowCount(0);
		if (uiIndustry.itemTypeSelector->currentText() == "Buildings")
		{
			for (auto & stck : colonies[selectedColony.value()].
				getIndustry().getBuildings()[row].first.getBuildCost())
			{
				uiIndustry.itemCostTable->insertRow(uiIndustry.itemCostTable->rowCount());

				auto actualRow = uiIndustry.itemCostTable->rowCount() - 1;
				uiIndustry.itemCostTable->setItem(actualRow, 0, new QTableWidgetItem(QString::fromStdString(stck.first.name)));
				uiIndustry.itemCostTable->setItem(actualRow, 1, new QTableWidgetItem(QString::number(stck.second)));
			}
		}
	});
}

void ColoniesWindow::setSelectedColony(QTreeWidgetItem * item, int column)
{
	for (size_t i = 0; i < colonies.size(); i++)
	{
		if (item->text(column) == colonies[i].getBody().getName())
		{
			selectedColony = i;
		}
	}
}

void ColoniesWindow::resetData()
{
	auto tabManagment = [&]
	{
		switch (previousTab)
		{
		case TabT::Summary:
			ui.contentLayout->removeWidget(&summary);
			summary.close();
			break;
		case TabT::Industry:
			ui.contentLayout->removeWidget(&industry);
			industry.close();
			break;
		case TabT::Mining:
			ui.contentLayout->removeWidget(&mining);
			mining.close();
			break;
		case TabT::Stockpile:
			ui.contentLayout->removeWidget(&stock);
			stock.close();
			break;
		case TabT::Economy:
			break;
		}
		previousTab = selectedTab;
	};

	if (ui.coloniesTree != nullptr)
	{
		ui.coloniesTree->clear();
		for (const auto & col : colonies)
		{
			ui.coloniesTree->addTopLevelItem(new QTreeWidgetItem(QStringList(col.getBody().getName())));
		}
		if (selectedColony.has_value())
		{
			if (selectedTab == TabT::Stockpile)
			{
				tabManagment();
				ui.contentLayout->addWidget(&stock);
				stock.show();

				uiStock.StockTable->setRowCount(0);
				const auto & stockPile = colonies[selectedColony.value()].getStockpile();
				auto usage = colonies[selectedColony.value()].getIndustry().getWeeklyUsageOfCommodities();
				auto prod = colonies[selectedColony.value()].getIndustry().getWeeklyProductionOfCommodities();

				for (size_t i = 0; i < stockPile.size(); i++)
				{
					uiStock.StockTable->insertRow(uiStock.StockTable->rowCount());

					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 0, 
						new QTableWidgetItem(QString::fromStdString(stockPile[i].first.name)));
					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(stockPile[i].second)));
					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(prod[i])));
					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(usage[i])));
				}
			}
			if (selectedTab == TabT::Mining)
			{
				tabManagment();
				ui.contentLayout->addWidget(&mining);
				mining.show();

				uiMining.miningTable->setRowCount(0);

				auto resNames = ResourceDeposit::getResourcesNames();
				auto & res = colonies[selectedColony.value()].getBody().getResources();
				const auto & stockRes = colonies[selectedColony.value()].getStockpile();
				auto resYield = colonies[selectedColony.value()].getWeeklyResourcesYield();

				for (size_t i = 0; i < res.get().size(); i++)
				{
					uiMining.miningTable->insertRow(uiMining.miningTable->rowCount());

					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(resNames[i])));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 1, new QTableWidgetItem(Calc::representValue<uint64_t>(res.accessDeposit(i).first)));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(res.accessDeposit(i).second)));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(stockRes[i].second)));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 4, new QTableWidgetItem(QString::number(resYield[i])));
				}
			}
			if (selectedTab == TabT::Summary)
			{
				tabManagment();
				ui.contentLayout->addWidget(&summary);
				summary.show();

				uiSummary.valuesTable->setRowCount(0);
				uiSummary.buildingsTable->setRowCount(0);

				auto & colIndustry = colonies[selectedColony.value()].getIndustry();

				using name_value = std::pair<QString, QString>;
				auto values = std::array<name_value, 2>({ 
					name_value("Energy Demand", QString::number(colIndustry.getEnergyDemand()) + " MW"),
					name_value("Energy Production", QString::number(colIndustry.getEnergyProduction()) + " MW") });

				auto ranges = { values.size(), colIndustry.getBuildings().size() };
				auto minmax = std::minmax_element(ranges.begin(), ranges.end());

				for (size_t i = 0; i < *minmax.second; i++)
				{
					if (i < values.size())
					{
						uiSummary.valuesTable->insertRow(uiSummary.valuesTable->rowCount());

						uiSummary.valuesTable->setItem(uiSummary.valuesTable->rowCount() - 1, 0, new QTableWidgetItem(values[i].first));
						uiSummary.valuesTable->setItem(uiSummary.valuesTable->rowCount() - 1, 1, new QTableWidgetItem(values[i].second));
					}
					if(i < colIndustry.getBuildings().size())
					{
						uiSummary.buildingsTable->insertRow(uiSummary.buildingsTable->rowCount());

						uiSummary.buildingsTable->setItem(uiSummary.buildingsTable->rowCount() - 1, 0,
							new QTableWidgetItem(QString::fromStdString(colIndustry.getBuildings()[i].first.getName())));
						uiSummary.buildingsTable->setItem(uiSummary.buildingsTable->rowCount() - 1, 1,
							new QTableWidgetItem(QString::number(colIndustry.getBuildings()[i].second)));
					}
				}
			}
			if (selectedTab == TabT::Industry)
			{
				tabManagment();
				ui.contentLayout->addWidget(&industry);
				industry.show();
			}
		}
	}
}