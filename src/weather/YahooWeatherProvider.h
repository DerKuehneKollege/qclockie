//
// Created by mumpi on 23.04.2016.
//

#ifndef QCLOCKIE_YAHOOWEATHERPROVIDER_H
#define QCLOCKIE_YAHOOWEATHERPROVIDER_H

#include <QtGui/QtGui>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "WeatherData.h"
#include "LocationData.h"

class YahooWeatherProvider : public QObject {
Q_OBJECT

public:
    YahooWeatherProvider();
    ~YahooWeatherProvider();

    inline bool isWoeidSet() {
        return !woeid.isEmpty();
    }

    inline QString getWoeid() {
        return this->woeid;
    }

    inline void setWoeid(const QString &woeid) {
        // todo check for validity, if not given info over qDebug and unsetWoeid
        this->woeid = woeid;
    }

    inline void unsetWoeid() {
        this->woeid = QString();
    }

    inline QString getLocationString() {
        return this->locationString;
    }

    inline void setLocationString(QString &locationString) {
        this->locationString = locationString;
    }

    void sendWeatherRequest();
    void sendSearchLocationRequest(QString &locationQueryString);
signals:
    void weatherUpdateAvailable(WeatherData weatherData);
    void weatherUpdateFailed(QString errorString);
    void locationSearchResultAvailable(QList<LocationData> *locationDataList);
    void locationSearchFailed(QString errorString);
private slots:
    void handleWeatherProviderReply(QNetworkReply *reply);
private:
    QNetworkAccessManager *networkAccessManager;
    QString woeid;
    QString locationString;

    QObject *weatherRequestObj;
    QObject *searchLocationRequestObj;

    void processWeatherUpdateJsonResponse(const QByteArray &jsonData);
    void processLocationSearchJsonResponse(const QByteArray &jsonData);
    QString getWeatherConditionStringByCode(int conditionCode);
    QString getWeatherConditionIconByCode(int conditionCode);

    inline bool hasValue(const QJsonObject &subject, QString valueKey) {
        if (!subject.contains(valueKey) || subject.value(valueKey).toString().isEmpty()) {
            qDebug() << "Response has invalid format, missing key:" << valueKey;
            emit weatherUpdateFailed("Response has invalid format");
            return false;
        }
        return true;
    }

    inline bool checkIsJsonObject(const QJsonObject &subject, QString valueKey) {
        if (!subject.contains(valueKey) || !subject.value(valueKey).isObject()) {
            qDebug() << "Response has invalid format, missing key or no JSON object:" << valueKey;
            emit weatherUpdateFailed("Response has invalid format");
            return false;
        }
        return true;
    }
};


#endif //QCLOCKIE_YAHOOWEATHERPROVIDER_H
