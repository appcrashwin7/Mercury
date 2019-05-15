#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), selectedColony(-1), previousTab(TabT::Undefined), selectedTab(TabT::Undefined)
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
}

void ColoniesWindow::setSelectedColony(QTreeWidgetItem * item, int column)
{
	for (size_t i = 0; i < colonies.size(); i++)
	{
		if (item->text(column).toStdString() == colonies[i].getPlanet().name)
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
		auto clearTable = [](QTableWidget * table)
		{
			table->clearContents();
			table->setRowCount(0);
		};

		ui.coloniesTree->clear();
		for (const auto & col : colonies)
		{
			ui.coloniesTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(col.getPlanet().name))));
		}
		if (selectedColony != -1)
		{
			if (selectedTab == TabT::Stockpile)
			{
				tabManagment();
				ui.contentLayout->addWidget(&stock);
				stock.show();

				clearTable(uiStock.StockTable);

				for (const auto & stockUnit : colonies[selectedColony].getStockpile())
				{
					uiStock.StockTable->insertRow(uiStock.StockTable->rowCount());

					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 0, 
						new QTableWidgetItem(QString::fromStdString(stockUnit.first.getName())));
					uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(stockUnit.second)));
				}
			}
			if (selectedTab == TabT::Mining)
			{
				tabManagment();
				ui.contentLayout->addWidget(&mining);
				mining.show();

				clearTable(uiMining.miningTable);

				auto resNames = ResourceDeposit::getResourcesNames();
				auto & res = colonies[selectedColony].getPlanet().accessResources();
				const auto & stockRes = colonies[selectedColony].getResourcesStockpile();

				for (size_t i = 0; i < res.getRes().size(); i++)
				{
					uiMining.miningTable->insertRow(uiMining.miningTable->rowCount());

					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(resNames[i])));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 1, new QTableWidgetItem(Calc::representValue<uint64_t>(res.accessDeposit(i).first)));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(res.accessDeposit(i).second)));
					uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 3, new QTableWidgetItem(QString::number(stockRes[i])));
				}
			}
			if (selectedTab == TabT::Summary)
			{
				tabManagment();
				ui.contentLayout->addWidget(&summary);
				summary.show();

				clearTable(uiSummary.valuesTable);
				clearTable(uiSummary.buildingsTable);

				auto & industry = colonies[selectedColony].getIndustry();
				using name_value = std::pair<QString, QString>;
				auto values = std::array<name_value, 2>({ name_value("Energy Demand", QString::number(industry.getEnergyDemand())),
					name_value("Energy Production", QString::number(industry.getEnergyProduction())) });
				auto ranges = { values.size(), industry.getBuildings().size() };
				auto minmax = std::minmax_element(ranges.begin(), ranges.end());

				for (size_t i = 0; i < *minmax.second; i++)
				{
					if (i < values.size())
					{
						uiSummary.valuesTable->insertRow(uiSummary.valuesTable->rowCount());

						uiSummary.valuesTable->setItem(uiSummary.valuesTable->rowCount() - 1, 0, new QTableWidgetItem(values[i].first));
						uiSummary.valuesTable->setItem(uiSummary.valuesTable->rowCount() - 1, 1, new QTableWidgetItem(values[i].second));
					}
					if(i < industry.getBuildings().size())
					{
						uiSummary.buildingsTable->insertRow(uiSummary.buildingsTable->rowCount());

						uiSummary.buildingsTable->setItem(uiSummary.buildingsTable->rowCount() - 1, 0, 
							new QTableWidgetItem(QString::fromStdString(industry.getBuildings()[i].first.name)));
						uiSummary.buildingsTable->setItem(uiSummary.buildingsTable->rowCount() - 1, 1,
							new QTableWidgetItem(QString::number(industry.getBuildings()[i].second)));
					}
				}
			}
		}
	}
}