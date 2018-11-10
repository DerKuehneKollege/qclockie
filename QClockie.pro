#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T09:45:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QClockie
TEMPLATE = app

SOURCES += src/main.cpp\
    src/lib/autostart/AutostartHelperWindows.cpp\
    src/lib/keyboardhook/KeyboardHookWindows.cpp\
    src/lib/runguard/RunGuard.cpp\
    src/tts/TextToSpeechInterface.cpp\
    src/tts/TimeAnnouncement.cpp\
    src/alarm/AlarmManager.cpp\
    src/gui/MainWindow.cpp\
    src/gui/devconsole/DevConsoleWidget.cpp\
    src/gui/settings/SettingsWidget.cpp\
    src/weather/YahooWeatherProvider.cpp\


HEADERS  += src/lib/autostart/AutostartHelper.h\
    src/lib/autostart/AutostartHelperWindows.h\
    src/lib/keyboardhook/KeyboardHookWindows.h\
    src/lib/runguard/RunGuard.h\
    src/tts/TextToSpeechInterface.h\
    src/tts/TimeAnnouncement.h\
    src/alarm/AlarmManager.h\
    src/gui/MainWindow.h\
    src/gui/devconsole/DevConsoleWidget.h\
    src/gui/settings/SettingsWidget.h\
    src/weather/YahooWeatherProvider.h\
    src/weather/WeatherData.h\
    src/weather/LocationData.h

FORMS    += src/gui/mainwindow.ui\
    src/gui/alarm/alarm.ui\
    src/gui/settings/settings.ui\
    src/gui/devconsole/devconsole.ui

LIBS += -lole32 -loleaut32 # ole32 and oleaut32 for Windows SAPI
