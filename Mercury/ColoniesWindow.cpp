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
		ui.coloniesTree->clear();
		for (const auto & col : colonies)
		{
			ui.coloniesTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(col.getPlanet().name))));
		}
		if (selectedTab == TabT::Stockpile && selectedColony != -1)
		{
			tabManagment();
			ui.contentLayout->addWidget(&stock);
			stock.show();

			uiStock.StockTable->clearContents();
			uiStock.StockTable->setRowCount(0);

			for (const auto stock : colonies[selectedColony].getStockpile())
			{
				uiStock.StockTable->insertRow(uiStock.StockTable->rowCount());
				uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(stock.first.getName())));
				uiStock.StockTable->setItem(uiStock.StockTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(stock.second)));
			}
		}
		if (selectedTab == TabT::Mining && selectedColony != -1)
		{
			tabManagment();
			ui.contentLayout->addWidget(&mining);
			mining.show();

			uiMining.miningTable->clearContents();
			uiMining.miningTable->setRowCount(0);

			auto resNames = ResourceDeposit::getResourcesNames();
			auto & depo = colonies[selectedColony].getPlanet().accessResources();

			for (size_t i = 0; i < depo.getRes().size(); i++)
			{
				uiMining.miningTable->insertRow(uiMining.miningTable->rowCount());
				uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(resNames[i])));
				uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(depo.accessDeposit(i).first)));
				uiMining.miningTable->setItem(uiMining.miningTable->rowCount() - 1, 2, new QTableWidgetItem(QString::number(depo.accessDeposit(i).second)));
			}
		}
	}
}