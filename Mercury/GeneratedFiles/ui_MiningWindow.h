/********************************************************************************
** Form generated from reading UI file 'MiningWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MININGWINDOW_H
#define UI_MININGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiningWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *miningInfo;

    void setupUi(QWidget *MiningWindow)
    {
        if (MiningWindow->objectName().isEmpty())
            MiningWindow->setObjectName(QStringLiteral("MiningWindow"));
        MiningWindow->resize(621, 527);
        verticalLayout = new QVBoxLayout(MiningWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        miningInfo = new QTableWidget(MiningWindow);
        if (miningInfo->columnCount() < 6)
            miningInfo->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        miningInfo->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        miningInfo->setObjectName(QStringLiteral("miningInfo"));
        miningInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        miningInfo->horizontalHeader()->setVisible(true);
        miningInfo->horizontalHeader()->setHighlightSections(true);
        miningInfo->horizontalHeader()->setStretchLastSection(true);
        miningInfo->verticalHeader()->setVisible(false);
        miningInfo->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(miningInfo);


        retranslateUi(MiningWindow);

        QMetaObject::connectSlotsByName(MiningWindow);
    } // setupUi

    void retranslateUi(QWidget *MiningWindow)
    {
        MiningWindow->setWindowTitle(QApplication::translate("MiningWindow", "Form", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = miningInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MiningWindow", "Resource", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = miningInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MiningWindow", "Deposit Size", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = miningInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MiningWindow", "Accessibility", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = miningInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MiningWindow", "Stock", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = miningInfo->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MiningWindow", "Weekly Yield", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = miningInfo->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MiningWindow", "Weekly Usage", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiningWindow: public Ui_MiningWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MININGWINDOW_H
