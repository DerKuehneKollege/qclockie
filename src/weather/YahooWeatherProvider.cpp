//
// Created by mumpi on 23.04.2016.
//

#include <QtNetwork/QNetworkRequest>
#include <QtCore/QUrl>
#include "YahooWeatherProvider.h"

// https://developer.yahoo.com/weather/
// https://developer.yahoo.com/weather/documentation.html
YahooWeatherProvider::YahooWeatherProvider() {
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleWeatherProviderReply(QNetworkReply*)));

    weatherRequestObj = new QObject();
    searchLocationRequestObj = new QObject();

    unsetWoeid();
}

YahooWeatherProvider::~YahooWeatherProvider() {
    delete networkAccessManager;
    delete weatherRequestObj;
    delete searchLocationRequestObj;
}

void YahooWeatherProvider::sendWeatherRequest() {
    if (!isWoeidSet()) {
        emit weatherUpdateFailed(tr("Kein Wetterort ausgewählt"));
        return;
    }

    QString yqlSearchLocationQuery = QString("select * from weather.forecast where woeid=%1 AND u='c'")
            .arg(getWoeid());
    QString yqlRequest = QString(  "http://query.yahooapis.com/v1/public/yql?q="
                                 + QUrl::toPercentEncoding(yqlSearchLocationQuery)
                                 + "&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");

    QNetworkRequest req;
    req.setOriginatingObject(weatherRequestObj);
    req.setUrl(QUrl(yqlRequest));
    networkAccessManager->get(req);
    qDebug() << "Request to Yahoo Weather API sent";
}

void YahooWeatherProvider::sendSearchLocationRequest(QString &locationQueryString) {
    // TODO purify input (no injection etc.)
    QString yqlSearchLocationQuery = QString("select * from geo.places where text='%1'")
            .arg(locationQueryString);
    QString yqlSearchLocationRequest = QString(  "http://query.yahooapis.com/v1/public/yql?q="
                                               + QUrl::toPercentEncoding(yqlSearchLocationQuery)
                                               + "&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");

    QNetworkRequest req;
    req.setOriginatingObject(searchLocationRequestObj);
    req.setUrl(QUrl(yqlSearchLocationRequest));
    networkAccessManager->get(req);
    qDebug() << "Request to Yahoo Weather API sent" << locationQueryString;
}

void YahooWeatherProvider::handleWeatherProviderReply(QNetworkReply *reply) {
    QObject *originatingObject = reply->request().originatingObject();
    if (originatingObject == weatherRequestObj) {
        // that's a response to a weather request, handle here
        if (reply->error() == QNetworkReply::NoError) {
            // success
            qDebug() << "Weather reply from Yahoo Weather API received";
            processWeatherUpdateJsonResponse(reply->readAll()); // handle reply
        } else {
            // failure
            QString errorString = reply->errorString().prepend("An error occurred when requesting weather from Yahoo Weather API: ");
            qDebug() << errorString;
            emit weatherUpdateFailed(errorString);
        }
    } else if (originatingObject == searchLocationRequestObj) {
        // that's a response to a search location request, handle here
        if (reply->error() == QNetworkReply::NoError) {
            // success
            qDebug() << "Search location reply from Yahoo Weather API received";
            processLocationSearchJsonResponse(reply->readAll()); // handle reply
        } else {
            // failure
            QString errorString = reply->errorString().prepend("An error occurred when requesting location from Yahoo Weather API: ");
            qDebug() << errorString;
            // TODO emit failure
        }
    } else {
        qDebug() << "Received unhandled response";
    }

    // reply can be deleted after handling (actually even if not handled)
    delete reply;
}

void YahooWeatherProvider::processWeatherUpdateJsonResponse(const QByteArray &jsonData) {
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);

    // error handling: valid JSON?
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error reading received JSON response";
        emit weatherUpdateFailed("Error reading received JSON response");
        return;
    }

    QJsonObject rootObject = jsonDocument.object();
    if (!checkIsJsonObject(rootObject, "query")) return;
    QJsonObject queryObject = rootObject.value("query").toObject();
    if (!checkIsJsonObject(queryObject, "results")) return;
    QJsonObject resultsObject = queryObject.value("results").toObject();
    if (!checkIsJsonObject(resultsObject, "channel")) return;
    QJsonObject channelObject = resultsObject.value("channel").toObject();

    if (!checkIsJsonObject(channelObject, "units")) return;
    QJsonObject unitsObject = channelObject.value("units").toObject();
    if (!checkIsJsonObject(channelObject, "location")) return;
    QJsonObject locationObject = channelObject.value("location").toObject();
    if (!checkIsJsonObject(channelObject, "item")) return;
    QJsonObject itemObject = channelObject.value("item").toObject();

    if (!checkIsJsonObject(itemObject, "condition")) return;
    QJsonObject conditionObject = itemObject.value("condition").toObject();

    // TODO is query count = 1?

    // sanity check
    if (!hasValue(channelObject, "lastBuildDate")) return;
    if (!hasValue(locationObject, "city")) return;
    if (!hasValue(locationObject, "region")) return;
    if (!hasValue(locationObject, "country")) return;
    if (!hasValue(unitsObject, "temperature")) return;
    if (!hasValue(conditionObject, "temp")) return;

    WeatherData weatherData;
    weatherData.captureDateTime = QDateTime::fromString(channelObject.value("lastBuildDate").toString(), Qt::RFC2822Date);
    weatherData.link = channelObject.value("link").toString("");
    weatherData.ttl = channelObject.value("ttl").toString("-1");
    weatherData.city = locationObject.value("city").toString();
    weatherData.region = locationObject.value("region").toString();
    weatherData.country = locationObject.value("country").toString();
    weatherData.temperatureUnit = unitsObject.value("temperature").toString();
    weatherData.temperature = conditionObject.value("temp").toString();

    // get condition
    int conditionCode = conditionObject.value("code").toString("-1").toInt();
    weatherData.conditionString = getWeatherConditionStringByCode(conditionCode);
    weatherData.conditionIcon = getWeatherConditionIconByCode(conditionCode);

    emit weatherUpdateAvailable(weatherData);
}

void YahooWeatherProvider::processLocationSearchJsonResponse(const QByteArray &jsonData) {
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);

    // error handling: valid JSON?
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error reading received JSON response";
        emit locationSearchFailed("Error reading received JSON response");
        return;
    }

    //qDebug() << QString(jsonDocument.toJson(QJsonDocument::Compact));

    QJsonObject rootObject = jsonDocument.object();
    if (!checkIsJsonObject(rootObject, "query")) return;
    QJsonObject queryObject = rootObject.value("query").toObject();

    // get count
    // TODO check if count is set
    // TODO Is count > 20? too many results! emit error
    int count = queryObject.value("count").toInt(0);
    qDebug() << "Location search result count:" << count;

    // if no results (or error), provide an empty list
    // todo or emit error?
    if (count <= 0) {
        locationSearchResultAvailable(new QList<LocationData>());
        return;
    }

    if (!checkIsJsonObject(queryObject, "results")) return;
    QJsonObject resultsObject = queryObject.value("results").toObject();

    // places array
    // TODO check if place is set
    QJsonValue placesValue = resultsObject.value("place");
    QJsonArray placesArray;
    if (placesValue.isArray()) {
        placesArray = resultsObject.value("place").toArray();
    } else {
        // if no array it is one value, consider it as array
        placesArray.append(resultsObject.value("place"));
    }

    QList<LocationData> *locationDataList = new QList<LocationData>();

    int i = 0;
    foreach (const QJsonValue &v, placesArray) {
        QJsonObject placeObject = v.toObject();

        qDebug()
            << "Result" << ++i
            << placeObject.value("name").toString()
            << placeObject.value("admin2").toObject().value("content").toString()
            << placeObject.value("admin1").toObject().value("content").toString()
            << placeObject.value("country").toObject().value("content").toString()
            << placeObject.value("woeid").toString();

        LocationData locationData;
        locationData.woeid = placeObject.value("woeid").toString();
        locationData.country = placeObject.value("country").toObject().value("content").toString();
        locationData.region = placeObject.value("admin1").toObject().value("content").toString();
        locationData.city = placeObject.value("name").toString();

        locationDataList->append(locationData);
    }

    emit locationSearchResultAvailable(locationDataList);
}

QString YahooWeatherProvider::getWeatherConditionStringByCode(int conditionCode) {
    // TODO use hashmap?
    // TODO check strings
    // source: https://developer.yahoo.com/weather/documentation.html#codes
    switch (conditionCode) {
        case 0:  return tr("Tornado"); // tornado
        case 1:  return tr("Tropensturm"); // tropical storm
        case 2:  return tr("Hurrikan"); // hurricane
        case 3:  return tr("Schwere Gewitter"); // severe thunderstorms
        case 4:  return tr("Gewitter"); // thunderstorms
        case 5:  return tr("Schneeregen"); // mixed rain and snow
        case 6:  return tr("Schneeregen"); // mixed rain and sleet
        case 7:  return tr("Schneeregen"); // mixed snow and sleet
        case 8:  return tr("Gefrierender Regen"); // freezing drizzle
        case 9:  return tr("Nieselregen"); // drizzle
        case 10: return tr("Eisregen"); // freezing rain
        case 11: return tr("Regenschauer"); // showers
        case 12: return tr("Regenschauer"); // showers
        case 13: return tr("Schneetreiben"); // snow flurries
        case 14: return tr("Leichter Schneeregen"); // light snow showers
        case 15: return tr("Flugschnee"); // blowing snow
        case 16: return tr("Schnee"); // snow
        case 17: return tr("Hagel"); // hail
        case 18: return tr("Eisregen"); // sleet
        case 19: return tr("Sandsturm"); // dust
        case 20: return tr("Nebel"); // foggy
        case 21: return tr("Nebel"); // haze
        case 22: return tr("Nebel"); // smoky
        case 23: return tr("Sturm"); // blustery
        case 24: return tr("Wind"); // windy
        case 25: return tr("Frost"); // cold
        case 26: return tr("Bewölkung"); // cloudy
        case 27: return tr("Meist bewölkt"); // mostly cloudy (night)
        case 28: return tr("Meist bewölkt"); // mostly cloudy (day)
        case 29: return tr("Teilweise wolkig"); // partly cloudy (night)
        case 30: return tr("Teilweise wolkig"); // partly cloudy (day)
        case 31: return tr("Klar"); // clear (night)
        case 32: return tr("Sonnig"); // sunny
        case 33: return tr("Heiter"); // fair (night)
        case 34: return tr("Heiter"); // fair (day)
        case 35: return tr("Hagelschauer"); // mixed rain and hail
        case 36: return tr("Hitze"); // hot
        case 37: return tr("Örtliche Gewitter"); // isolated thunderstorms
        case 38: return tr("Vereinzelte Gewitter"); // scattered thunderstorms
        case 39: return tr("Vereinzelte Gewitter"); // scattered thunderstorms
        case 40: return tr("Vereinzelte Schauer"); // scattered showers
        case 41: return tr("Schwere Schneefälle"); // heavy snow
        case 42: return tr("Vereinzelt Schneefälle"); // scattered snow showers
        case 43: return tr("Schwere Schneefälle"); // heavy snow
        case 44: return tr("Teilweise wolkig"); // partly cloudy
        case 45: return tr("Gewitterschauer"); // thundershowers
        case 46: return tr("Schneeschauer"); // snow showers
        case 47: return tr("Vereinzelte Gewitter"); // isolated thundershowers

        default: return tr("Unbekannt"); // not available
    }
}

QString YahooWeatherProvider::getWeatherConditionIconByCode(int conditionCode) {
    // TODO use hashmap?
    // TODO write readable weather icon name
    // https://erikflowers.github.io/weather-icons/
    switch (conditionCode) {
        case 0:  return QString::fromUtf8("\uf056"); // tornado
        case 1:  return QString::fromUtf8("\uf01e"); // tropical storm
        case 2:  return QString::fromUtf8("\uf073"); // hurricane
        case 3:  return QString::fromUtf8("\uf01e"); // severe thunderstorms
        case 4:  return QString::fromUtf8("\uf01d"); // thunderstorms
        case 5:  return QString::fromUtf8("\uf0b5"); // mixed rain and snow
        case 6:  return QString::fromUtf8("\uf0b5"); // mixed rain and sleet
        case 7:  return QString::fromUtf8("\uf0b5"); // mixed snow and sleet
        case 8:  return QString::fromUtf8("\uf017"); // freezing drizzle
        case 9:  return QString::fromUtf8("\uf017"); // drizzle
        case 10: return QString::fromUtf8("\uf017"); // freezing rain
        case 11: return QString::fromUtf8("\uf01a"); // showers
        case 12: return QString::fromUtf8("\uf01a"); // showers
        case 13: return QString::fromUtf8("\uf01b"); // snow flurries
        case 14: return QString::fromUtf8("\uf01b"); // light snow showers
        case 15: return QString::fromUtf8("\uf064"); // blowing snow
        case 16: return QString::fromUtf8("\uf01b"); // snow
        case 17: return QString::fromUtf8("\uf015"); // hail
        case 18: return QString::fromUtf8("\uf0b5"); // sleet
        case 19: return QString::fromUtf8("\uf063"); // dust
        case 20: return QString::fromUtf8("\uf014"); // foggy
        case 21: return QString::fromUtf8("\uf0b6"); // haze
        case 22: return QString::fromUtf8("\uf062"); // smoky
        case 23: return QString::fromUtf8("\uf011"); // blustery
        case 24: return QString::fromUtf8("\uf021"); // windy
        case 25: return QString::fromUtf8("\uf076"); // cold
        case 26: return QString::fromUtf8("\uf013"); // cloudy
        case 27: return QString::fromUtf8("\uf013"); // mostly cloudy (night)
        case 28: return QString::fromUtf8("\uf013"); // mostly cloudy (day)
        case 29: return QString::fromUtf8("\uf041"); // partly cloudy (night)
        case 30: return QString::fromUtf8("\uf041"); // partly cloudy (day)
        case 31: return QString::fromUtf8("\uf02e"); // clear (night)
        case 32: return QString::fromUtf8("\uf00d"); // sunny
        case 33: return QString::fromUtf8("\uf02e"); // fair (night)
        case 34: return QString::fromUtf8("\uf00d"); // fair (day)
        case 35: return QString::fromUtf8("\uf017"); // mixed rain and hail
        case 36: return QString::fromUtf8("\uf072"); // hot
        case 37: return QString::fromUtf8("\uf016"); // isolated thunderstorms
        case 38: return QString::fromUtf8("\uf01d"); // scattered thunderstorms
        case 39: return QString::fromUtf8("\uf01d"); // scattered thunderstorms
        case 40: return QString::fromUtf8("\uf01c"); // scattered showers
        case 41: return QString::fromUtf8("\uf064"); // heavy snow
        case 42: return QString::fromUtf8("\uf01b"); // scattered snow showers
        case 43: return QString::fromUtf8("\uf064"); // heavy snow
        case 44: return QString::fromUtf8("\uf013"); // partly cloudy
        case 45: return QString::fromUtf8("\uf01d"); // thundershowers
        case 46: return QString::fromUtf8("\uf0b5"); // snow showers
        case 47: return QString::fromUtf8("\uf016"); // isolated thundershowers

        default: return QString::fromUtf8("\uf07b"); // not available
    }
}
