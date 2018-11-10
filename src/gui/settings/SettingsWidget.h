//
// Created by mumpi on 05.05.2016.
//

#ifndef QCLOCKIE_SETTINGSWIDGET_H
#define QCLOCKIE_SETTINGSWIDGET_H

#include <QtWidgets/QWidget>

#include "ui_settings.h"
#include "../../weather/YahooWeatherProvider.h"

namespace Ui {
    class SettingsWidget;
}

class SettingsWidget : public QWidget {
Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    void setWeatherProvider(YahooWeatherProvider *weatherProvider);
    ~SettingsWidget();

private slots:
    void searchWeatherLocation();
    void handleSearchWeatherLocationResponse(QList<LocationData>* locationDataList);
    void handleSearchWeatherLocationError(QString errorString);
    void selectWeatherLocation();
    void weatherLocationChanged(int index);

private:
    Ui::SettingsWidget *ui;
    YahooWeatherProvider *weatherProvider;
};


#endif //QCLOCKIE_SETTINGSWIDGET_H
