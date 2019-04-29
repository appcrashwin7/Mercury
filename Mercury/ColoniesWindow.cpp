#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), selectedColony(-1)
{
	ui.setupUi(this);

	QObject::connect(getColoniesTree(), &QTreeWidget::itemClicked, this, &ColoniesWindow::setSelectedColony);
	QObject::connect(getButton("summary"), &QPushButton::clicked, [=] {this->selectedTab = TabT::Summary; resetData(); });
	QObject::connect(getButton("industry"), &QPushButton::clicked, [=] {this->selectedTab = TabT::Industry; resetData(); });
	QObject::connect(getButton("mining"), &QPushButton::clicked, [=] {this->selectedTab = TabT::Mining; resetData(); });
	QObject::connect(getButton("stock"), &QPushButton::clicked, [=] {this->selectedTab = TabT::Stockpile; resetData(); });
	QObject::connect(getButton("economy"), &QPushButton::clicked, [=] {this->selectedTab = TabT::Economy; resetData(); });
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

QTreeWidget * ColoniesWindow::getColoniesTree()
{
	return this->findChild<QTreeWidget*>("coloniesTree");
}

QPushButton * ColoniesWindow::getButton(const std::string & name)
{
	return this->findChild<QPushButton*>(QString::fromStdString(name));
}

QWidget * ColoniesWindow::getContent()
{
	return this->findChild<QWidget*>("content");
}

void ColoniesWindow::resetData()
{
	if (getColoniesTree() != nullptr)
	{
		getColoniesTree()->clear();
		for (const auto & col : colonies)
		{
			getColoniesTree()->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(col.getPlanet().name))));
		}
		if (selectedTab == TabT::Stockpile && selectedColony != -1)
		{
			uiStock.setupUi(getContent());
			QTableWidget * stockTable = getContent()->findChild<QTableWidget*>("StockTable");
			stockTable->clearContents();
			stockTable->setRowCount(0);

			for (const auto stock : colonies[selectedColony].getStockpile())
			{
				stockTable->insertRow(stockTable->rowCount());
				stockTable->setItem(stockTable->rowCount() - 1, stockTable->columnCount() - 2, new QTableWidgetItem(QString::fromStdString(stock.first.getName())));
				stockTable->setItem(stockTable->rowCount() - 1, stockTable->columnCount() - 1, new QTableWidgetItem(QString::number(stock.second)));
			}
		}
	}
}