//
// Created by mumpi on 31.03.2016.
//

#ifndef QCLOCKIE_MAINWINDOW_H
#define QCLOCKIE_MAINWINDOW_H

static const int TIME_UPDATE_INTERVAL_MSEC = 100; // every 100 msec
static const int WEATHER_UPDATE_INTERVAL_MSEC = 1200000; // every 20 minutes

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtGui/QMouseEvent>
#include <QtGui/QContextMenuEvent>

#include "../lib/autostart/AutostartHelper.h"
#include "../tts/TextToSpeechInterface.h"
#include "../tts/TimeAnnouncement.h"
#include "../lib/keyboardhook/KeyboardHookWindows.h"
#include "../weather/YahooWeatherProvider.h"
#include "devconsole/DevConsoleWidget.h"
#include "settings/SettingsWidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    static DevConsoleWidget *devConsoleWidget;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:
    void handleWindowKeyPressEvent(QKeyEvent *keyEvent);
    void systrayIconActivated(QSystemTrayIcon::ActivationReason activationReason);
    void setAutostartOnOsStartup(bool shallAutostart);
    void setWindowStaysOnTop(bool staysOnTop);
    void setShowSeconds(bool showSeconds);
    void setSayTimePeriodically(bool sayTimePeriodically);
    void showSettings();
    void minimizeWindow();
    void updateWeather();
    void handleWeatherUpdate(WeatherData weatherData);
    void handleWeatherUpdateFailed(QString errorString);
    void updateTime();
    void sayTime();
    void loadSettings();
    void saveSettings();
    void handleUpdatedSettings();
    void quitProgram();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *systrayIcon;
    QPoint dragPosition;

    SettingsWidget *settingsWidget;

    TextToSpeechInterface *ttsInterface;
    TimeAnnouncement *timeAnnouncement;
    KeyboardHookWindows *keyboardHook;
    YahooWeatherProvider *weatherProvider;

    QTimer *updateTimeTimer;
    QTimer *updateWeatherTimer;

    QString settingsFileName;
    QString timeFormatString;

    QMenu *systrayMenu;
    QMenu *windowContextMenu;

    QAction *windowStaysOnTopAction;
    QAction *autostartWithOsAction;
    QAction *showSecondsAction;
    QAction *showSettingsAction;
    QAction *weatherAction;
    QAction *sayTimeAction;
    QAction *sayTimePeriodicallyAction;
    QAction *minimizeAction;
    QAction *closeAction;

    void setupWindowProperties();
    void setupWeatherIconFont();
    void createMenuActions();
    void createSystrayIcon();
    void createWindowContextMenu();
    void resetWindowPosition();
};

#endif //QCLOCKIE_MAINWINDOW_H
