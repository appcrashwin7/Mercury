#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), selectedColony(-1)
{
	ui.setupUi(this);
	QObject::connect(getColoniesTree(), &QTreeWidget::itemClicked, this, &ColoniesWindow::setSelectedColony);


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

void ColoniesWindow::resetData()
{
	if (getColoniesTree() != nullptr)
	{
		getColoniesTree()->clear();
		for (const auto & col : colonies)
		{
			getColoniesTree()->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(col.getPlanet().name))));
		}
	}
}