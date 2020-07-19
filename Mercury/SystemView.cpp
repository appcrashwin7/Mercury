#include "SystemView.h"

SystemView::SystemView(std::vector<Colony>* cl, Universe* u)
    :QWidget(nullptr), cls(cl), universe(u)
{
    ui.setupUi(this);

    auto systemsList = this->findChild<QListWidget*>("systemsList");
    QObject::connect(systemsList, &QListWidget::itemClicked, this, &SystemView::fillSystemTable);
}

void SystemView::reset()
{
    fillSystemsList();
}

void SystemView::fillSystemsList()
{
    auto systemList = this->findChild<QListWidget*>("systemsList");
    systemList->clear();
    for (const auto& s : universe->getSystems())
    {
        systemList->addItem(s.getName());
    }
}

void SystemView::fillSystemTable(QListWidgetItem* item)
{
    if (item == nullptr)
    {
        return;
    }

    auto selectedSystemName = item->text();

    auto selectedSystem = std::find_if(universe->getSystems().begin(), universe->getSystems().end(), 
        [selectedSystemName](const PlanetarySystem& s)
        {
            if (s.getName() == selectedSystemName)
            {
                return true;
            }
            return false;
        });
    auto table = this->findChild<QTableWidget*>("systemTable");
    table->clearContents();
    table->setRowCount(0);

    if (selectedSystem != universe->getSystems().end())
    {
        for (const auto& p : selectedSystem.operator->()->Bodies)
        {
            const auto dtSize = table->columnCount();
            auto dt = std::vector<QString>{ p.get()->getName(), "",
            TemperatureToText(p.get()->physics.getSurfaceTemperature()),
            AccelerationToText(p.get()->surfaceGravity, false, false),
            LengthToText(p.get()->physics.radius, true, false), "", "" };

            fillNewRow(table, dt); 
        }
    }
}
