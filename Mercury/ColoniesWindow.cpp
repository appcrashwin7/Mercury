#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), previousTab(TabT::Summary), selectedTab(TabT::Summary)
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
	QObject::connect(uiIndustry.createButton, &QPushButton::clicked, [&]()
	{
		if (!selectedColony)
		{
			return;
		}

		bool ok;
		int32_t amount = uiIndustry.amountLineEdit->text().toInt(&ok, 10);
		uiIndustry.amountLineEdit->setText("");

		auto item = uiIndustry.itemsTable->selectedItems().first()->text().toStdString();
		if (uiIndustry.itemTypeSelector->currentText() == QString("Buildings"))
		{
			auto building = std::find_if(colonies[selectedColony.value()].getIndustry().getBuildings().begin(),
				colonies[selectedColony.value()].getIndustry().getBuildings().end(),
				[item](const BuildingQuantityT & b)
			{
				if (b.first.getName() == item)
				{
					return true;
				}
				return false;
			});
			auto ID = std::distance(colonies[selectedColony.value()].getIndustry().getBuildings().begin(),
				building);
			colonies[selectedColony.value()].getIndustry().
				addNewConstruction(Construction(static_cast<size_t>(ID), amount, QDate()));
		}
		fillIndustry();
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
			tabManagment();

			switch (selectedTab)
			{
			case TabT::Summary:
				fillSummary();
				ui.contentLayout->addWidget(&summary);
				summary.show();
				break;
			case TabT::Industry:
				fillIndustry();
				ui.contentLayout->addWidget(&industry);
				industry.show();
				break;
			case TabT::Mining:
				fillMining();
				ui.contentLayout->addWidget(&mining);
				mining.show();
				break;
			case TabT::Stockpile:
				ui.contentLayout->addWidget(&stock);
				stock.show();
				fillStock();
				break;
			case TabT::Economy:
				break;
			default:
				break;
			}
		}
	}
}

void ColoniesWindow::fillSummary()
{
	uiSummary.valuesTable->setRowCount(0);
	uiSummary.buildingsTable->setRowCount(0);

	auto & actualColony = colonies[selectedColony.value()];
	auto & colIndustry = actualColony.getIndustry();

	constexpr size_t valRowSize = 2;
	using name_value = std::array<QString, valRowSize>;
	auto values = std::array<name_value, 3>({
		name_value{"Energy Demand", QString::number(colIndustry.getEnergyDemand()) + " MW"},
		name_value{"Energy Production", QString::number(colIndustry.getEnergyProduction()) + " MW"},
		name_value{"Construction Capability", QString::number(colIndustry.getConstructionCapability())} });

	auto ranges = { values.size(), colIndustry.getBuildings().size() };
	auto minmax = std::minmax_element(ranges.begin(), ranges.end());

	std::array<QString, valRowSize> bdt;

	for (size_t i = 0; i < *minmax.second; i++)
	{
		if (i < values.size())
		{
			fillNewRow<valRowSize>(uiSummary.valuesTable, values[i]);
		}
		if (i < colIndustry.getBuildings().size())
		{
			bdt = { QString::fromStdString(colIndustry.getBuildings()[i].first.getName()),
			QString::number(colIndustry.getBuildings()[i].second) };
			fillNewRow<valRowSize>(uiSummary.buildingsTable, bdt);
		}
	}
}

void ColoniesWindow::fillStock()
{
	uiStock.StockTable->setRowCount(0);
	auto & actualColony = colonies[selectedColony.value()];

	auto & stockpile = actualColony.getStockpile();
	auto usage = actualColony.getIndustry().getWeeklyUsageOfCommodities();
	auto prod = actualColony.getIndustry().getWeeklyProductionOfCommodities();

	constexpr size_t arrSize = 4;
	std::array<QString, arrSize> dt;

	for (size_t i = 0; i < stockpile.size(); i++)
	{
		dt = { QString::fromStdString(stockpile[i].first.name) , QString::number(stockpile[i].second),
			QString::number(prod[i]), QString::number(usage[i]) };

		fillNewRow<arrSize>(uiStock.StockTable, dt);
	}
}

void ColoniesWindow::fillIndustry()
{
	uiIndustry.currentProjectsTable->setRowCount(0);

	constexpr size_t arrSize = 5;
	std::array<QString, arrSize> dt;
	auto & currentColony = colonies[selectedColony.value()];

	for (auto & constr : currentColony.getIndustry().getConstructionQueue())
	{
		dt = { QString::fromStdString(currentColony.getIndustry().getBuildings()[constr.getBuildingID()].first.getName()),
		QString::number(constr.getAmount()), QString::number(constr.getConstructionCost()),
		constr.getETC().toString(), Construction::StatusToQString(constr.getStatus()) };

		fillNewRow<arrSize>(uiIndustry.currentProjectsTable, dt);
	}
}

void ColoniesWindow::fillMining()
{
	uiMining.miningTable->setRowCount(0);
	auto & actualColony = colonies[selectedColony.value()];

	auto resNames = ResourceDeposit::getResourcesNames();
	auto & res = actualColony.getBody().getResources();
	const auto & stockRes = actualColony.getStockpile();
	auto resYield = actualColony.getWeeklyResourcesYield();

	constexpr size_t arrSize = 5;
	std::array<QString, arrSize> dt;

	for (size_t i = 0; i < res.get().size(); i++)
	{
		dt = { QString::fromStdString(resNames[i]), Calc::representValue<uint64_t>(res.accessDeposit(i).first),
		QString::number(res.accessDeposit(i).second), QString::number(stockRes[i].second), QString::number(resYield[i]) };

		fillNewRow<arrSize>(uiMining.miningTable, dt);
	}
}