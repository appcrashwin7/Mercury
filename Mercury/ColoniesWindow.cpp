#include "ColoniesWindow.h"

ColoniesWindow::ColoniesWindow(std::vector<Colony> & cl)
	:QWidget(nullptr), colonies(cl), selectedColony(-1)
{
	ui.setupUi(this);
}

void ColoniesWindow::resetData()
{
	QTreeWidget * colsTree = this->findChild<QTreeWidget*>("coloniesTree");
	if (colsTree != nullptr)
	{
		for (const auto & col : colonies)
		{
			colsTree->addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(col.getPlanet().name + " colony"))));
		}
	}
}