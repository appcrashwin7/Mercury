#include "SystemView.h"

SystemView::SystemView(std::vector<Colony>* cl, Universe* u)
    :QWidget(nullptr), cls(cl), universe(u)
{
    ui.setupUi(this);

    auto systemsList = this->findChild<QListWidget*>("systemsList");
    auto systemTable = this->findChild<QTableWidget*>("systemTable");
    QObject::connect(systemsList, &QListWidget::itemClicked, this, &SystemView::fillSystemTable);
    QObject::connect(systemTable, &QTableWidget::itemClicked, this, &SystemView::fillMineralsTable);
}

void SystemView::reset()
{
    fillSystemsList();
}

void SystemView::fillMineralsTable(QTableWidgetItem* item)
{
    auto mtable = this->findChild<QTableWidget*>("mineralsTable");
    mtable->clearContents();
    mtable->setRowCount(0);

    auto selectedSystemName = this->findChild<QListWidget*>("systemsList")->selectedItems();
    auto planetID = item->row();

    if (!selectedSystemName.isEmpty() && planetID != -1)
    {
        auto systemName = selectedSystemName.first()->text();
        auto system = this->universe->getSystem(systemName);

        if (system != nullptr)
        {
            const auto & deposit = system->Bodies[planetID]->getResources();
            if (!deposit.isNotGenerated() && !deposit.isEmpty())
            {
                for (size_t i = 0; i < RESOURCES_LIST_SIZE; i++)
                {
                    std::vector<QString> dt = { QString::fromStdString(deposit.getResourcesNames()[i]),
                        Calc::representValue(deposit[i].first) };
                   fillNewRow(mtable, dt);
                }
            }
        }
    }

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
