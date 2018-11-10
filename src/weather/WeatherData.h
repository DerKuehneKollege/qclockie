//
// Created by mumpi on 24.04.2016.
//

#ifndef QCLOCKIE_WEATHERDATA_H
#define QCLOCKIE_WEATHERDATA_H

#include <QtCore/QString>
#include <QtCore/QDateTime>

struct WeatherData {
    QDateTime captureDateTime;
    QString city;
    QString region;
    QString country;
    QString temperatureUnit;
    QString temperature;
    QString conditionString;
    QString conditionIcon;
    QString link;
    QString ttl;
};

#endif //QCLOCKIE_WEATHERDATA_H
