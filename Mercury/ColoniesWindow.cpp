#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl)
{
	ui.setupUi(this);

	QObject::connect(ui.coloniesTree, &QTreeWidget::itemClicked, this, &ColoniesWindow::setSelectedColony);

	std::array<QPushButton*, static_cast<size_t>(TabT::Economy) + 1> buttons =
	{ ui.summary, ui.industry, ui.mining, ui.stock, ui.economy };

	for (int i = 0; i < buttons.size(); i++)
	{
		QObject::connect(buttons[i], &QPushButton::clicked, [=] {this->tabs.first = static_cast<TabT>(i); resetData(); });
	}

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
			constexpr size_t arrSize = 1;
			std::array<QString, arrSize> dt;

			for (auto & b : colonies[selectedColony.value()].getIndustry().getBuildings())
			{
				dt = { QString::fromStdString(b.first.getName()) };
				fillNewRow<arrSize>(uiIndustry.itemsTable, dt);
			}
		}
	});
	QObject::connect(uiIndustry.itemsTable, &QTableWidget::cellClicked, [&](int row, int column)
	{
		column;
		uiIndustry.itemCostTable->setRowCount(0);

		constexpr size_t arrSize = 2;
		std::array<QString, arrSize> dt;

		if (uiIndustry.itemTypeSelector->currentText() == "Buildings")
		{
			for (auto & stck : colonies[selectedColony.value()].
				getIndustry().getBuildings()[row].first.getBuildCost())
			{
				dt = { QString::fromStdString(stck.first.name), QString::number(stck.second) };
				fillNewRow<arrSize>(uiIndustry.itemCostTable, dt);
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
			colonies[selectedColony.value()].
				addNewConstruction(static_cast<size_t>(ID), amount);
		}
		fillIndustry();
	});
	QObject::connect(uiIndustry.modifyButton, &QPushButton::clicked, [&]()
	{
		uint64_t newAmount = static_cast<uint64_t>(uiIndustry.amountLineEdit->text().toInt());
		uiIndustry.amountLineEdit->setText("");
		size_t constructionIndex = static_cast<size_t>(uiIndustry.currentProjectsTable->currentRow());

		colonies[selectedColony.value()].setConstructionAmount(newAmount, constructionIndex);
		fillIndustry();
	});
	QObject::connect(uiIndustry.cancelButton, &QPushButton::clicked, [&]()
	{
		size_t constructionIndex = static_cast<size_t>(uiIndustry.currentProjectsTable->currentRow());
		colonies[selectedColony.value()].cancelConstruction(constructionIndex);
		fillIndustry();
	});
	QObject::connect(uiIndustry.pauseButton, &QPushButton::clicked, [&]()
	{
		size_t constructionIndex = static_cast<size_t>(uiIndustry.currentProjectsTable->currentRow());
		colonies[selectedColony.value()].pauseConstruction(constructionIndex);
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
		switch (tabs.second)
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
		tabs.second = tabs.first;
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

			switch (tabs.first)
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

	for (auto & constr : currentColony.getConstructionQueue())
	{
		dt = { QString::fromStdString(currentColony.getIndustry().getBuildings()[constr.getBuildingID()].first.getName()),
		QString::number(constr.getAmount()), QString::number(constr.getConstructionCost()),
		QString::number(constr.getETC()), Construction::StatusToQString(constr.getStatus()) };

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