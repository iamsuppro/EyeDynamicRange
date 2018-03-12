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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "drawareaedr.h"

QT_BEGIN_NAMESPACE

class Ui_EyeDynamicRangeClass
{
public:
    QAction *actionFull_Screen;
    QAction *actionShow_Controls;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    DrawAreaEDR *mainDrawArea;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QLabel *label_4;
    QSlider *calibrationHoriz;
    QSlider *calibrationVert;
    QLabel *label_5;
    QGroupBox *groupBox;
    QPushButton *tobiiReconnect;
    QLabel *tobiiLabel;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menuOptions;

    void setupUi(QMainWindow *EyeDynamicRangeClass)
    {
        if (EyeDynamicRangeClass->objectName().isEmpty())
            EyeDynamicRangeClass->setObjectName(QStringLiteral("EyeDynamicRangeClass"));
        EyeDynamicRangeClass->resize(1021, 728);
        actionFull_Screen = new QAction(EyeDynamicRangeClass);
        actionFull_Screen->setObjectName(QStringLiteral("actionFull_Screen"));
        actionFull_Screen->setCheckable(true);
        actionShow_Controls = new QAction(EyeDynamicRangeClass);
        actionShow_Controls->setObjectName(QStringLiteral("actionShow_Controls"));
        actionShow_Controls->setCheckable(true);
        actionShow_Controls->setChecked(true);
        centralWidget = new QWidget(EyeDynamicRangeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        mainDrawArea = new DrawAreaEDR(centralWidget);
        mainDrawArea->setObjectName(QStringLiteral("mainDrawArea"));

        horizontalLayout->addWidget(mainDrawArea);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(250, 0));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(15, 120, 211, 161));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 30, 91, 21));
        calibrationHoriz = new QSlider(groupBox_4);
        calibrationHoriz->setObjectName(QStringLiteral("calibrationHoriz"));
        calibrationHoriz->setGeometry(QRect(20, 60, 171, 22));
        calibrationHoriz->setMinimum(-200);
        calibrationHoriz->setMaximum(200);
        calibrationHoriz->setValue(0);
        calibrationHoriz->setOrientation(Qt::Horizontal);
        calibrationVert = new QSlider(groupBox_4);
        calibrationVert->setObjectName(QStringLiteral("calibrationVert"));
        calibrationVert->setGeometry(QRect(20, 120, 171, 22));
        calibrationVert->setMinimum(-200);
        calibrationVert->setMaximum(200);
        calibrationVert->setValue(0);
        calibrationVert->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 90, 91, 21));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(15, 20, 211, 81));
        tobiiReconnect = new QPushButton(groupBox);
        tobiiReconnect->setObjectName(QStringLiteral("tobiiReconnect"));
        tobiiReconnect->setGeometry(QRect(120, 30, 81, 31));
        tobiiLabel = new QLabel(groupBox);
        tobiiLabel->setObjectName(QStringLiteral("tobiiLabel"));
        tobiiLabel->setGeometry(QRect(10, 30, 101, 31));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        tobiiLabel->setFont(font);
        tobiiLabel->setAlignment(Qt::AlignCenter);
        tobiiLabel->raise();
        tobiiReconnect->raise();
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        EyeDynamicRangeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EyeDynamicRangeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1021, 21));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        EyeDynamicRangeClass->setMenuBar(menuBar);

        menuBar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionFull_Screen);
        menuOptions->addSeparator();
        menuOptions->addAction(actionShow_Controls);

        retranslateUi(EyeDynamicRangeClass);
        QObject::connect(actionFull_Screen, SIGNAL(toggled(bool)), EyeDynamicRangeClass, SLOT(onFullscreen(bool)));
        QObject::connect(actionShow_Controls, SIGNAL(toggled(bool)), EyeDynamicRangeClass, SLOT(onShowControls(bool)));
        QObject::connect(tobiiReconnect, SIGNAL(clicked()), EyeDynamicRangeClass, SLOT(onTobiiReconnectClicked()));
        QObject::connect(calibrationVert, SIGNAL(valueChanged(int)), EyeDynamicRangeClass, SLOT(onCalibrationVertChanged(int)));
        QObject::connect(calibrationHoriz, SIGNAL(valueChanged(int)), EyeDynamicRangeClass, SLOT(onCalibrationHorizChanged(int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EyeDynamicRangeClass);
    } // setupUi

    void retranslateUi(QMainWindow *EyeDynamicRangeClass)
    {
        EyeDynamicRangeClass->setWindowTitle(QApplication::translate("EyeDynamicRangeClass", "EyeDynamicRange", nullptr));
        actionFull_Screen->setText(QApplication::translate("EyeDynamicRangeClass", "Full Screen", nullptr));
        actionShow_Controls->setText(QApplication::translate("EyeDynamicRangeClass", "Show Controls", nullptr));
        mainDrawArea->setText(QApplication::translate("EyeDynamicRangeClass", "TextLabel", nullptr));
        groupBox_4->setTitle(QApplication::translate("EyeDynamicRangeClass", "Calibration", nullptr));
        label_4->setText(QApplication::translate("EyeDynamicRangeClass", "Horizontal Offset:", nullptr));
        label_5->setText(QApplication::translate("EyeDynamicRangeClass", "Vertical Offset:", nullptr));
        groupBox->setTitle(QApplication::translate("EyeDynamicRangeClass", "Tobii", nullptr));
        tobiiReconnect->setText(QApplication::translate("EyeDynamicRangeClass", "Reconnect", nullptr));
        tobiiLabel->setText(QApplication::translate("EyeDynamicRangeClass", "Disconnected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EyeDynamicRangeClass", "General", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EyeDynamicRangeClass", "Image", nullptr));
        menuOptions->setTitle(QApplication::translate("EyeDynamicRangeClass", "Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EyeDynamicRangeClass: public Ui_EyeDynamicRangeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EYEDYNAMICRANGE_H
