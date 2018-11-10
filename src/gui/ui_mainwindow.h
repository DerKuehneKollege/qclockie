/********************************************************************************
** Form generated from reading UI file 'mainwindowp10776.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWP10776_H
#define MAINWINDOWP10776_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelTime;
    QLabel *labelDate;
    QHBoxLayout *hLayoutWeather;
    QSpacerItem *horizontalSpacer;
    QLabel *labelWeatherIcon;
    QLabel *labelWeather;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(303, 155);
        MainWindow->setWindowOpacity(1);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(-1, -1, -1, 8);
        labelTime = new QLabel(centralWidget);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI Light"));
        font.setPointSize(55);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        labelTime->setFont(font);
        labelTime->setStyleSheet(QStringLiteral("QLabel { color:white; }"));
        labelTime->setTextFormat(Qt::AutoText);
        labelTime->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        labelTime->setWordWrap(false);
        labelTime->setMargin(0);
        labelTime->setIndent(-1);

        verticalLayout->addWidget(labelTime);

        labelDate = new QLabel(centralWidget);
        labelDate->setObjectName(QStringLiteral("labelDate"));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        font1.setPointSize(12);
        labelDate->setFont(font1);
        labelDate->setStyleSheet(QStringLiteral("QLabel { color:white; }"));
        labelDate->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(labelDate);

        hLayoutWeather = new QHBoxLayout();
        hLayoutWeather->setSpacing(6);
        hLayoutWeather->setObjectName(QStringLiteral("hLayoutWeather"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutWeather->addItem(horizontalSpacer);

        labelWeatherIcon = new QLabel(centralWidget);
        labelWeatherIcon->setObjectName(QStringLiteral("labelWeatherIcon"));
        labelWeatherIcon->setMaximumSize(QSize(25, 25));
        QFont font2;
        font2.setStyleStrategy(QFont::PreferDefault);
        labelWeatherIcon->setFont(font2);
        labelWeatherIcon->setStyleSheet(QStringLiteral("QLabel { color:white; }"));
        labelWeatherIcon->setScaledContents(false);
        labelWeatherIcon->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        hLayoutWeather->addWidget(labelWeatherIcon);

        labelWeather = new QLabel(centralWidget);
        labelWeather->setObjectName(QStringLiteral("labelWeather"));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI"));
        font3.setPointSize(10);
        font3.setKerning(true);
        font3.setStyleStrategy(QFont::PreferDefault);
        labelWeather->setFont(font3);
        labelWeather->setContextMenuPolicy(Qt::NoContextMenu);
        labelWeather->setStyleSheet(QStringLiteral("QLabel { color:white; }"));
        labelWeather->setAlignment(Qt::AlignCenter);

        hLayoutWeather->addWidget(labelWeather);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutWeather->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(hLayoutWeather);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QClockie", 0));
        labelTime->setText(QApplication::translate("MainWindow", "12:00", 0));
        labelDate->setText(QApplication::translate("MainWindow", "Montag, 01. Januar 1970", 0));
        labelWeatherIcon->setText(QString());
        labelWeather->setText(QApplication::translate("MainWindow", "Keine Wetterdaten verf\303\274gbar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWP10776_H
