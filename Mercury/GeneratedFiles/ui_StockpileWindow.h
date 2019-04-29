/********************************************************************************
** Form generated from reading UI file 'StockpileWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKPILEWINDOW_H
#define UI_STOCKPILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *StockTable;

    void setupUi(QWidget *StockWindow)
    {
        if (StockWindow->objectName().isEmpty())
            StockWindow->setObjectName(QStringLiteral("StockWindow"));
        StockWindow->resize(645, 631);
        verticalLayout = new QVBoxLayout(StockWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        StockTable = new QTableWidget(StockWindow);
        if (StockTable->columnCount() < 2)
            StockTable->setColumnCount(2);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setForeground(brush);
        StockTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        StockTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        StockTable->setObjectName(QStringLiteral("StockTable"));
        StockTable->setMaximumSize(QSize(16777215, 16777215));
        StockTable->setLayoutDirection(Qt::LeftToRight);
        StockTable->setAutoFillBackground(false);
        StockTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        StockTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        StockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        StockTable->setAlternatingRowColors(false);
        StockTable->setSelectionMode(QAbstractItemView::NoSelection);
        StockTable->setTextElideMode(Qt::ElideNone);
        StockTable->setSortingEnabled(false);
        StockTable->setWordWrap(true);
        StockTable->horizontalHeader()->setVisible(true);
        StockTable->horizontalHeader()->setCascadingSectionResizes(false);
        StockTable->horizontalHeader()->setHighlightSections(true);
        StockTable->horizontalHeader()->setMinimumSectionSize(37);
        StockTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        StockTable->horizontalHeader()->setStretchLastSection(true);
        StockTable->verticalHeader()->setVisible(false);
        StockTable->verticalHeader()->setHighlightSections(true);
        StockTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(StockTable);


        retranslateUi(StockWindow);

        QMetaObject::connectSlotsByName(StockWindow);
    } // setupUi

    void retranslateUi(QWidget *StockWindow)
    {
        StockWindow->setWindowTitle(QApplication::translate("StockWindow", "Stockpile", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = StockTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("StockWindow", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = StockTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("StockWindow", "Quanity", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StockWindow: public Ui_StockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKPILEWINDOW_H
