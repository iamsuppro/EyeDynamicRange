/********************************************************************************
** Form generated from reading UI file 'EyeDynamicRange.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EYEDYNAMICRANGE_H
#define UI_EYEDYNAMICRANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EyeDynamicRangeClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *EyeDynamicRangeClass)
    {
        if (EyeDynamicRangeClass->objectName().isEmpty())
            EyeDynamicRangeClass->setObjectName(QStringLiteral("EyeDynamicRangeClass"));
        EyeDynamicRangeClass->resize(1021, 728);
        centralWidget = new QWidget(EyeDynamicRangeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        EyeDynamicRangeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EyeDynamicRangeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1021, 21));
        EyeDynamicRangeClass->setMenuBar(menuBar);

        retranslateUi(EyeDynamicRangeClass);

        QMetaObject::connectSlotsByName(EyeDynamicRangeClass);
    } // setupUi

    void retranslateUi(QMainWindow *EyeDynamicRangeClass)
    {
        EyeDynamicRangeClass->setWindowTitle(QApplication::translate("EyeDynamicRangeClass", "EyeDynamicRange", nullptr));
        label->setText(QApplication::translate("EyeDynamicRangeClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EyeDynamicRangeClass: public Ui_EyeDynamicRangeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EYEDYNAMICRANGE_H
