/********************************************************************************
** Form generated from reading UI file 'ColoniesWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLONIESWINDOW_H
#define UI_COLONIESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColonyWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *summary;
    QPushButton *industry;
    QPushButton *mining;
    QPushButton *economy;
    QPushButton *pushButton;
    QWidget *content;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ColonyWidget)
    {
        if (ColonyWidget->objectName().isEmpty())
            ColonyWidget->setObjectName(QStringLiteral("ColonyWidget"));
        ColonyWidget->resize(1142, 706);
        gridLayout = new QGridLayout(ColonyWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        summary = new QPushButton(ColonyWidget);
        summary->setObjectName(QStringLiteral("summary"));

        horizontalLayout->addWidget(summary);

        industry = new QPushButton(ColonyWidget);
        industry->setObjectName(QStringLiteral("industry"));

        horizontalLayout->addWidget(industry);

        mining = new QPushButton(ColonyWidget);
        mining->setObjectName(QStringLiteral("mining"));

        horizontalLayout->addWidget(mining);

        economy = new QPushButton(ColonyWidget);
        economy->setObjectName(QStringLiteral("economy"));

        horizontalLayout->addWidget(economy);

        pushButton = new QPushButton(ColonyWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        content = new QWidget(ColonyWidget);
        content->setObjectName(QStringLiteral("content"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(content->sizePolicy().hasHeightForWidth());
        content->setSizePolicy(sizePolicy);

        gridLayout->addWidget(content, 1, 1, 1, 1);

        treeWidget = new QTreeWidget(ColonyWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(treeWidget, 0, 0, 2, 1);


        retranslateUi(ColonyWidget);

        QMetaObject::connectSlotsByName(ColonyWidget);
    } // setupUi

    void retranslateUi(QWidget *ColonyWidget)
    {
        ColonyWidget->setWindowTitle(QApplication::translate("ColonyWidget", "Colonies", Q_NULLPTR));
        summary->setText(QApplication::translate("ColonyWidget", "Summary", Q_NULLPTR));
        industry->setText(QApplication::translate("ColonyWidget", "Industry", Q_NULLPTR));
        mining->setText(QApplication::translate("ColonyWidget", "Mining", Q_NULLPTR));
        economy->setText(QApplication::translate("ColonyWidget", "Economy", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ColonyWidget", "PushButton", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("ColonyWidget", "Colonized Systems", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ColonyWidget: public Ui_ColonyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLONIESWINDOW_H
