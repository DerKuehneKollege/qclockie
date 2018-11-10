/********************************************************************************
** Form generated from reading UI file 'settingsp11932.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGSP11932_H
#define SETTINGSP11932_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWidget
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *mainVerticalLayout;
    QTabWidget *settingsTabWidget;
    QWidget *generalTab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *generalVerticalLayout;
    QGroupBox *programOptionsGroupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *startWithWindowsCheckBox;
    QCheckBox *keepInForegroundCheckBox;
    QWidget *designTab;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *designVerticalLayout;
    QGroupBox *designGeneralGroupBox;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *designGeneralVerticalLayout;
    QCheckBox *showSecondsCheckBox;
    QGroupBox *designColorGroupBox;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *designColorVerticalLayout;
    QPushButton *foregroundColorButton;
    QPushButton *backgroundColorButton;
    QLabel *foregroundColorLabel;
    QLabel *backgroundColorLabel;
    QSpacerItem *designVerticalSpacer;
    QWidget *timeAnnouncementTab;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *timeAnnouncementVerticalLayout;
    QGroupBox *timeAnnouncementGeneralGroupBox;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *timeAnnouncementGeneralVerticalLayout;
    QCheckBox *timeAnnouncementCheckBox;
    QGroupBox *timeAnnouncementIntervalGroupBox;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *timeAnnouncementIntervalVerticalLayout;
    QRadioButton *everyQuarterRadioButton;
    QRadioButton *everyHalfHourRadioButton;
    QRadioButton *everyHourRadioButton;
    QSpacerItem *timeAnnouncementVerticalSpacer;
    QWidget *weatherTab;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *weatherVerticalLayout;
    QGroupBox *weatherGeneralGroupBox;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *weatherGeneralVerticalLayout;
    QCheckBox *enableWeatherCheckBox;
    QGroupBox *weatherLocationGroupBox;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *weatherLocationVerticalLayout;
    QComboBox *weatherLocationComboBox;
    QPushButton *searchLocationButton;
    QPushButton *selectLocationButton;
    QLabel *selectedLocationLabel;
    QSpacerItem *weatherVerticalSpacer;

    void setupUi(QWidget *SettingsWidget)
    {
        if (SettingsWidget->objectName().isEmpty())
            SettingsWidget->setObjectName(QStringLiteral("SettingsWidget"));
        SettingsWidget->resize(437, 420);
        gridLayout_2 = new QGridLayout(SettingsWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        mainVerticalLayout = new QVBoxLayout();
        mainVerticalLayout->setObjectName(QStringLiteral("mainVerticalLayout"));
        settingsTabWidget = new QTabWidget(SettingsWidget);
        settingsTabWidget->setObjectName(QStringLiteral("settingsTabWidget"));
        generalTab = new QWidget();
        generalTab->setObjectName(QStringLiteral("generalTab"));
        verticalLayout_3 = new QVBoxLayout(generalTab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        generalVerticalLayout = new QVBoxLayout();
        generalVerticalLayout->setObjectName(QStringLiteral("generalVerticalLayout"));
        generalVerticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        programOptionsGroupBox = new QGroupBox(generalTab);
        programOptionsGroupBox->setObjectName(QStringLiteral("programOptionsGroupBox"));
        programOptionsGroupBox->setMaximumSize(QSize(16777215, 100));
        verticalLayout_2 = new QVBoxLayout(programOptionsGroupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        startWithWindowsCheckBox = new QCheckBox(programOptionsGroupBox);
        startWithWindowsCheckBox->setObjectName(QStringLiteral("startWithWindowsCheckBox"));
        startWithWindowsCheckBox->setEnabled(false);

        verticalLayout->addWidget(startWithWindowsCheckBox);

        keepInForegroundCheckBox = new QCheckBox(programOptionsGroupBox);
        keepInForegroundCheckBox->setObjectName(QStringLiteral("keepInForegroundCheckBox"));
        keepInForegroundCheckBox->setEnabled(false);

        verticalLayout->addWidget(keepInForegroundCheckBox);


        verticalLayout_2->addLayout(verticalLayout);


        generalVerticalLayout->addWidget(programOptionsGroupBox, 0, Qt::AlignTop);


        verticalLayout_3->addLayout(generalVerticalLayout);

        settingsTabWidget->addTab(generalTab, QString());
        designTab = new QWidget();
        designTab->setObjectName(QStringLiteral("designTab"));
        verticalLayout_13 = new QVBoxLayout(designTab);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        designVerticalLayout = new QVBoxLayout();
        designVerticalLayout->setObjectName(QStringLiteral("designVerticalLayout"));
        designGeneralGroupBox = new QGroupBox(designTab);
        designGeneralGroupBox->setObjectName(QStringLiteral("designGeneralGroupBox"));
        designGeneralGroupBox->setMaximumSize(QSize(16777215, 100));
        verticalLayout_19 = new QVBoxLayout(designGeneralGroupBox);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        designGeneralVerticalLayout = new QVBoxLayout();
        designGeneralVerticalLayout->setObjectName(QStringLiteral("designGeneralVerticalLayout"));
        showSecondsCheckBox = new QCheckBox(designGeneralGroupBox);
        showSecondsCheckBox->setObjectName(QStringLiteral("showSecondsCheckBox"));
        showSecondsCheckBox->setEnabled(false);

        designGeneralVerticalLayout->addWidget(showSecondsCheckBox);


        verticalLayout_19->addLayout(designGeneralVerticalLayout);


        designVerticalLayout->addWidget(designGeneralGroupBox, 0, Qt::AlignTop);

        designColorGroupBox = new QGroupBox(designTab);
        designColorGroupBox->setObjectName(QStringLiteral("designColorGroupBox"));
        verticalLayout_21 = new QVBoxLayout(designColorGroupBox);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        designColorVerticalLayout = new QVBoxLayout();
        designColorVerticalLayout->setObjectName(QStringLiteral("designColorVerticalLayout"));
        foregroundColorButton = new QPushButton(designColorGroupBox);
        foregroundColorButton->setObjectName(QStringLiteral("foregroundColorButton"));
        foregroundColorButton->setEnabled(false);

        designColorVerticalLayout->addWidget(foregroundColorButton);

        backgroundColorButton = new QPushButton(designColorGroupBox);
        backgroundColorButton->setObjectName(QStringLiteral("backgroundColorButton"));
        backgroundColorButton->setEnabled(false);

        designColorVerticalLayout->addWidget(backgroundColorButton);

        foregroundColorLabel = new QLabel(designColorGroupBox);
        foregroundColorLabel->setObjectName(QStringLiteral("foregroundColorLabel"));
        foregroundColorLabel->setEnabled(false);

        designColorVerticalLayout->addWidget(foregroundColorLabel);

        backgroundColorLabel = new QLabel(designColorGroupBox);
        backgroundColorLabel->setObjectName(QStringLiteral("backgroundColorLabel"));
        backgroundColorLabel->setEnabled(false);

        designColorVerticalLayout->addWidget(backgroundColorLabel);


        verticalLayout_21->addLayout(designColorVerticalLayout);


        designVerticalLayout->addWidget(designColorGroupBox, 0, Qt::AlignTop);

        designVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        designVerticalLayout->addItem(designVerticalSpacer);


        verticalLayout_13->addLayout(designVerticalLayout);

        settingsTabWidget->addTab(designTab, QString());
        timeAnnouncementTab = new QWidget();
        timeAnnouncementTab->setObjectName(QStringLiteral("timeAnnouncementTab"));
        verticalLayout_5 = new QVBoxLayout(timeAnnouncementTab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        timeAnnouncementVerticalLayout = new QVBoxLayout();
        timeAnnouncementVerticalLayout->setObjectName(QStringLiteral("timeAnnouncementVerticalLayout"));
        timeAnnouncementGeneralGroupBox = new QGroupBox(timeAnnouncementTab);
        timeAnnouncementGeneralGroupBox->setObjectName(QStringLiteral("timeAnnouncementGeneralGroupBox"));
        verticalLayout_8 = new QVBoxLayout(timeAnnouncementGeneralGroupBox);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        timeAnnouncementGeneralVerticalLayout = new QVBoxLayout();
        timeAnnouncementGeneralVerticalLayout->setObjectName(QStringLiteral("timeAnnouncementGeneralVerticalLayout"));
        timeAnnouncementCheckBox = new QCheckBox(timeAnnouncementGeneralGroupBox);
        timeAnnouncementCheckBox->setObjectName(QStringLiteral("timeAnnouncementCheckBox"));
        timeAnnouncementCheckBox->setEnabled(false);

        timeAnnouncementGeneralVerticalLayout->addWidget(timeAnnouncementCheckBox);


        verticalLayout_8->addLayout(timeAnnouncementGeneralVerticalLayout);


        timeAnnouncementVerticalLayout->addWidget(timeAnnouncementGeneralGroupBox, 0, Qt::AlignTop);

        timeAnnouncementIntervalGroupBox = new QGroupBox(timeAnnouncementTab);
        timeAnnouncementIntervalGroupBox->setObjectName(QStringLiteral("timeAnnouncementIntervalGroupBox"));
        verticalLayout_9 = new QVBoxLayout(timeAnnouncementIntervalGroupBox);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        timeAnnouncementIntervalVerticalLayout = new QVBoxLayout();
        timeAnnouncementIntervalVerticalLayout->setObjectName(QStringLiteral("timeAnnouncementIntervalVerticalLayout"));
        everyQuarterRadioButton = new QRadioButton(timeAnnouncementIntervalGroupBox);
        everyQuarterRadioButton->setObjectName(QStringLiteral("everyQuarterRadioButton"));
        everyQuarterRadioButton->setEnabled(false);

        timeAnnouncementIntervalVerticalLayout->addWidget(everyQuarterRadioButton);

        everyHalfHourRadioButton = new QRadioButton(timeAnnouncementIntervalGroupBox);
        everyHalfHourRadioButton->setObjectName(QStringLiteral("everyHalfHourRadioButton"));
        everyHalfHourRadioButton->setEnabled(false);

        timeAnnouncementIntervalVerticalLayout->addWidget(everyHalfHourRadioButton);

        everyHourRadioButton = new QRadioButton(timeAnnouncementIntervalGroupBox);
        everyHourRadioButton->setObjectName(QStringLiteral("everyHourRadioButton"));
        everyHourRadioButton->setEnabled(false);
        everyHourRadioButton->setChecked(true);

        timeAnnouncementIntervalVerticalLayout->addWidget(everyHourRadioButton);


        verticalLayout_9->addLayout(timeAnnouncementIntervalVerticalLayout);


        timeAnnouncementVerticalLayout->addWidget(timeAnnouncementIntervalGroupBox, 0, Qt::AlignTop);

        timeAnnouncementVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        timeAnnouncementVerticalLayout->addItem(timeAnnouncementVerticalSpacer);


        verticalLayout_5->addLayout(timeAnnouncementVerticalLayout);

        settingsTabWidget->addTab(timeAnnouncementTab, QString());
        weatherTab = new QWidget();
        weatherTab->setObjectName(QStringLiteral("weatherTab"));
        verticalLayout_11 = new QVBoxLayout(weatherTab);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        weatherVerticalLayout = new QVBoxLayout();
        weatherVerticalLayout->setObjectName(QStringLiteral("weatherVerticalLayout"));
        weatherGeneralGroupBox = new QGroupBox(weatherTab);
        weatherGeneralGroupBox->setObjectName(QStringLiteral("weatherGeneralGroupBox"));
        verticalLayout_15 = new QVBoxLayout(weatherGeneralGroupBox);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        weatherGeneralVerticalLayout = new QVBoxLayout();
        weatherGeneralVerticalLayout->setObjectName(QStringLiteral("weatherGeneralVerticalLayout"));
        enableWeatherCheckBox = new QCheckBox(weatherGeneralGroupBox);
        enableWeatherCheckBox->setObjectName(QStringLiteral("enableWeatherCheckBox"));
        enableWeatherCheckBox->setEnabled(false);

        weatherGeneralVerticalLayout->addWidget(enableWeatherCheckBox);


        verticalLayout_15->addLayout(weatherGeneralVerticalLayout);


        weatherVerticalLayout->addWidget(weatherGeneralGroupBox, 0, Qt::AlignTop);

        weatherLocationGroupBox = new QGroupBox(weatherTab);
        weatherLocationGroupBox->setObjectName(QStringLiteral("weatherLocationGroupBox"));
        verticalLayout_17 = new QVBoxLayout(weatherLocationGroupBox);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        weatherLocationVerticalLayout = new QVBoxLayout();
        weatherLocationVerticalLayout->setObjectName(QStringLiteral("weatherLocationVerticalLayout"));
        weatherLocationComboBox = new QComboBox(weatherLocationGroupBox);
        weatherLocationComboBox->setObjectName(QStringLiteral("weatherLocationComboBox"));
        weatherLocationComboBox->setEditable(true);

        weatherLocationVerticalLayout->addWidget(weatherLocationComboBox);

        searchLocationButton = new QPushButton(weatherLocationGroupBox);
        searchLocationButton->setObjectName(QStringLiteral("searchLocationButton"));

        weatherLocationVerticalLayout->addWidget(searchLocationButton);

        selectLocationButton = new QPushButton(weatherLocationGroupBox);
        selectLocationButton->setObjectName(QStringLiteral("selectLocationButton"));

        weatherLocationVerticalLayout->addWidget(selectLocationButton);

        selectedLocationLabel = new QLabel(weatherLocationGroupBox);
        selectedLocationLabel->setObjectName(QStringLiteral("selectedLocationLabel"));

        weatherLocationVerticalLayout->addWidget(selectedLocationLabel);


        verticalLayout_17->addLayout(weatherLocationVerticalLayout);


        weatherVerticalLayout->addWidget(weatherLocationGroupBox, 0, Qt::AlignTop);

        weatherVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        weatherVerticalLayout->addItem(weatherVerticalSpacer);


        verticalLayout_11->addLayout(weatherVerticalLayout);

        settingsTabWidget->addTab(weatherTab, QString());

        mainVerticalLayout->addWidget(settingsTabWidget);


        gridLayout_2->addLayout(mainVerticalLayout, 0, 0, 1, 1);


        retranslateUi(SettingsWidget);

        settingsTabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingsWidget)
    {
        SettingsWidget->setWindowTitle(QApplication::translate("SettingsWidget", "Einstellungen", 0));
        programOptionsGroupBox->setTitle(QApplication::translate("SettingsWidget", "Programmoptionen", 0));
        startWithWindowsCheckBox->setText(QApplication::translate("SettingsWidget", "Mit Windows starten", 0));
        keepInForegroundCheckBox->setText(QApplication::translate("SettingsWidget", "Im Vordergrund halten", 0));
        settingsTabWidget->setTabText(settingsTabWidget->indexOf(generalTab), QApplication::translate("SettingsWidget", "Allgemein", 0));
        designGeneralGroupBox->setTitle(QApplication::translate("SettingsWidget", "Allgemein", 0));
        showSecondsCheckBox->setText(QApplication::translate("SettingsWidget", "Sekunden anzeigen", 0));
        designColorGroupBox->setTitle(QApplication::translate("SettingsWidget", "Farbauswahl", 0));
        foregroundColorButton->setText(QApplication::translate("SettingsWidget", "Vordergrundfarbe ausw\303\244hlen", 0));
        backgroundColorButton->setText(QApplication::translate("SettingsWidget", "Hintergrundfarbe ausw\303\244hlen", 0));
        foregroundColorLabel->setText(QApplication::translate("SettingsWidget", "Vordergrundfarbe", 0));
        backgroundColorLabel->setText(QApplication::translate("SettingsWidget", "Hintergrundfarbe", 0));
        settingsTabWidget->setTabText(settingsTabWidget->indexOf(designTab), QApplication::translate("SettingsWidget", "Design", 0));
        timeAnnouncementGeneralGroupBox->setTitle(QApplication::translate("SettingsWidget", "Allgemein", 0));
        timeAnnouncementCheckBox->setText(QApplication::translate("SettingsWidget", "Zeitansage aktivieren", 0));
        timeAnnouncementIntervalGroupBox->setTitle(QApplication::translate("SettingsWidget", "H\303\244ufigkeit", 0));
        everyQuarterRadioButton->setText(QApplication::translate("SettingsWidget", "Jede Viertelstunde", 0));
        everyHalfHourRadioButton->setText(QApplication::translate("SettingsWidget", "Jede halbe Stunde", 0));
        everyHourRadioButton->setText(QApplication::translate("SettingsWidget", "Jede Stunde", 0));
        settingsTabWidget->setTabText(settingsTabWidget->indexOf(timeAnnouncementTab), QApplication::translate("SettingsWidget", "Zeitansage", 0));
        weatherGeneralGroupBox->setTitle(QApplication::translate("SettingsWidget", "Allgemein", 0));
        enableWeatherCheckBox->setText(QApplication::translate("SettingsWidget", "Wetterbericht aktivieren", 0));
        weatherLocationGroupBox->setTitle(QApplication::translate("SettingsWidget", "Ort", 0));
        searchLocationButton->setText(QApplication::translate("SettingsWidget", "Suchen", 0));
        selectLocationButton->setText(QApplication::translate("SettingsWidget", "Ausw\303\244hlen", 0));
        selectedLocationLabel->setText(QApplication::translate("SettingsWidget", "Bitte w\303\244hlen Sie einen Ort aus.", 0));
        settingsTabWidget->setTabText(settingsTabWidget->indexOf(weatherTab), QApplication::translate("SettingsWidget", "Wetter", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsWidget: public Ui_SettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTINGSP11932_H
