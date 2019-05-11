/********************************************************************************
** Form generated from reading UI file 'SummaryWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMMARYWINDOW_H
#define UI_SUMMARYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SummaryWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *valuesTable;
    QTableWidget *buildingsTable;

    void setupUi(QWidget *SummaryWindow)
    {
        if (SummaryWindow->objectName().isEmpty())
            SummaryWindow->setObjectName(QStringLiteral("SummaryWindow"));
        SummaryWindow->resize(790, 637);
        horizontalLayout = new QHBoxLayout(SummaryWindow);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        valuesTable = new QTableWidget(SummaryWindow);
        if (valuesTable->columnCount() < 2)
            valuesTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        valuesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        valuesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        valuesTable->setObjectName(QStringLiteral("valuesTable"));
        valuesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        valuesTable->setSelectionMode(QAbstractItemView::NoSelection);
        valuesTable->setShowGrid(true);
        valuesTable->horizontalHeader()->setVisible(true);
        valuesTable->horizontalHeader()->setStretchLastSection(false);
        valuesTable->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(valuesTable);

        buildingsTable = new QTableWidget(SummaryWindow);
        if (buildingsTable->columnCount() < 2)
            buildingsTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        buildingsTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        buildingsTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        buildingsTable->setObjectName(QStringLiteral("buildingsTable"));
        buildingsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        buildingsTable->setSelectionMode(QAbstractItemView::NoSelection);

        horizontalLayout->addWidget(buildingsTable);


        retranslateUi(SummaryWindow);

        QMetaObject::connectSlotsByName(SummaryWindow);
    } // setupUi

    void retranslateUi(QWidget *SummaryWindow)
    {
        SummaryWindow->setWindowTitle(QApplication::translate("SummaryWindow", "Summary", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = valuesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SummaryWindow", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = valuesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SummaryWindow", "Value", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = buildingsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SummaryWindow", "Building", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = buildingsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("SummaryWindow", "Number", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SummaryWindow: public Ui_SummaryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMMARYWINDOW_H
