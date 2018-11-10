#include <QtCore/QStandardPaths>
#include <QtCore/QDateTime>
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtGui/QPainter>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QDesktopWidget>

#include "MainWindow.h"
#include "ui_mainwindow.h"

DevConsoleWidget * MainWindow::devConsoleWidget = nullptr;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // initialize dev console (happens at first so output can be read on console as early as possible)
    devConsoleWidget = new DevConsoleWidget();
    devConsoleWidget->setWindowFlags(Qt::Window);
    devConsoleWidget->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical));

    // init variables
    timeFormatString = QStringLiteral("hh:mm");
    ttsInterface = new TextToSpeechInterface(this);
    timeAnnouncement = new TimeAnnouncement();
    settingsWidget = nullptr;

    setupWindowProperties();
    setupWeatherIconFont();

    createMenuActions();
    createSystrayIcon();
    createWindowContextMenu();

    // setup weather provider
    weatherProvider = new YahooWeatherProvider();
    connect(weatherProvider, SIGNAL(weatherUpdateAvailable(WeatherData)), this, SLOT(handleWeatherUpdate(WeatherData)));
    connect(weatherProvider, SIGNAL(weatherUpdateFailed(QString)), this, SLOT(handleWeatherUpdateFailed(QString)));

    // setup settings module
    settingsFileName = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/qclockie.ini";
    connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(saveSettings())); // save settings on close
    loadSettings(); // try to load settings from file or load default settings (TODO: remove dependency to YahooWeatherProvider)
    handleUpdatedSettings(); // apply loaded settings

    // start timer that updates the time
    updateTimeTimer = new QTimer(this);
    connect(updateTimeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    updateTimeTimer->start(TIME_UPDATE_INTERVAL_MSEC);

    // setup keyboard hook
    keyboardHook = KeyboardHookWindows::getInstance();
    connect(keyboardHook, SIGNAL(sayTimeKeyPressed()), this, SLOT(sayTime()));
    keyboardHook->connect();

    // update weather, start timer to update every given interval
    updateWeather();
    updateWeatherTimer = new QTimer(this);
    connect(updateWeatherTimer, SIGNAL(timeout()), this, SLOT(updateWeather()));
    updateWeatherTimer->start(WEATHER_UPDATE_INTERVAL_MSEC);
}

MainWindow::~MainWindow() {
    if (keyboardHook) {
        keyboardHook->disconnect();
    }

    if (devConsoleWidget != nullptr) {
        delete devConsoleWidget;
    }

    delete ui;
}



/* ========== Overriden methods of MainWindow ========== */

void MainWindow::paintEvent(QPaintEvent *) {
    // paint window with a transparent black background, this allows to keep the child elements opaque
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 64)); // background color
    painter.drawRect(0, 0, width(), height());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    switch (event->button()) {
        case Qt::LeftButton:
            // when the window is lift clicked start drag-to-move mode, save current window position
            setCursor(Qt::SizeAllCursor);
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
            break;
        case Qt::MiddleButton:
            windowStaysOnTopAction->toggle();
            event->accept();
            break;
        default:
            break;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    // handle window movement when mouse is clicked
    if (event->buttons() & Qt::LeftButton) {
        setCursor(Qt::SizeAllCursor);
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    // open context menu if window is right-clicked
    windowContextMenu->exec(event->globalPos());
}



/* ========== SLOTs ========== */

void MainWindow::handleWindowKeyPressEvent(QKeyEvent *keyEvent) {
    if (keyEvent->key() == Qt::Key_F12) {
        // show debug window when F12 is pressed
        qDebug() << "F12 pressed, debug window is shown";

        // mark event as handled
        keyEvent->accept();

        if (devConsoleWidget->isHidden()) {
            // display window, if not already shown
            devConsoleWidget->show();
        }

        // focus window
        devConsoleWidget->activateWindow();
    } else {
        // otherwise further propagate event
        QMainWindow::keyPressEvent(keyEvent);
    }
}

void MainWindow::systrayIconActivated(QSystemTrayIcon::ActivationReason activationReason) {
    if (activationReason == QSystemTrayIcon::DoubleClick) {
        // minimize/restore window on double click of systray icon
        minimizeAction->trigger();
    }
}

void MainWindow::setAutostartOnOsStartup(bool shallAutostart) {
    if (shallAutostart) {
        AutostartHelper::setAutostartActivated();
        // check if it worked or throw error otherwise
        if (!AutostartHelper::isAutostartActivated()) {
            QMessageBox::warning(
                this,
                tr("Warnung"),
                tr("Anwendung konnte nicht als Autostart-Anwendung gesetzt werden."),
                QMessageBox::Ok
            );
            autostartWithOsAction->blockSignals(true);
            autostartWithOsAction->setChecked(false);
            autostartWithOsAction->blockSignals(false);
            return;
        }
        qDebug() << "Autostart activated";
    } else {
        AutostartHelper::setAutostartDeactivated();
        // check if it worked or throw error otherwise
        if (AutostartHelper::isAutostartActivated()) {
            QMessageBox::warning(
                this,
                tr("Warnung"),
                tr("Anwendung konnte nicht von den Autostart-Anwendungen entfernt werden."),
                QMessageBox::Ok
            );
            return;
        }
        qDebug() << "Autostart deactivated";
    }
}

void MainWindow::setWindowStaysOnTop(bool staysOnTop) {
    if (staysOnTop) {
        // add window stays on top flag
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        // remove window stays on top flag
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    }

    show();
}

void MainWindow::setShowSeconds(bool showSeconds) {
    if (showSeconds) {
        timeFormatString = QStringLiteral("hh:mm:ss");
    } else {
        timeFormatString = QStringLiteral("hh:mm");
    }
}

void MainWindow::setSayTimePeriodically(bool sayTimePeriodically) {
    if (sayTimePeriodically) {
        // enable time announcement
        connect(timeAnnouncement, SIGNAL(nextFullHourReached()), this, SLOT(sayTime()));
        timeAnnouncement->startFullHourTimeAnnouncement();
        qDebug() << "Activated periodic announcement of the time";
    } else {
        // disable time announcement
        timeAnnouncement->stopTimeAnnouncement();
        disconnect(timeAnnouncement, SIGNAL(nextFullHourReached()), this, SLOT(sayTime()));
        qDebug() << "Deactivated periodic announcement of the time";
    }
}

void MainWindow::showSettings() {
    // lazy initialization, only initialize settings if necessary
    if (settingsWidget == nullptr) {
        settingsWidget = new SettingsWidget();
        settingsWidget->setWeatherProvider(weatherProvider);
        settingsWidget->setWindowFlags(Qt::Window);
        settingsWidget->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
    }

    if (settingsWidget->isHidden()) {
        // display window, if not already shown
        settingsWidget->show();
    }
    // focus window
    settingsWidget->activateWindow();
}

void MainWindow::minimizeWindow() {
    if (isMinimized()) {
        minimizeAction->setText(tr("&Minimieren"));
        setWindowState(Qt::WindowActive);
    } else {
        minimizeAction->setText(tr("&Wiederherstellen"));
        setWindowState(Qt::WindowMinimized);
    }
}

void MainWindow::updateWeather() {
    ui->labelWeather->setText(tr("Aktualisiere Wetterdaten..."));
    ui->labelWeatherIcon->setText(QString::fromUtf8("\uf04c")); // wi-refresh
    weatherProvider->sendWeatherRequest();
}

void MainWindow::handleWeatherUpdate(WeatherData weatherData) {
    QString weatherString = QString()
        .append(weatherData.city)
        .append(", ")
        .append(weatherData.temperature).append(" °").append(weatherData.temperatureUnit)
        .append(", ")
        .append(weatherData.conditionString);

    ui->labelWeather->setOpenExternalLinks(true);
    ui->labelWeather->setText("<a href=\"" + weatherData.link + "\" style=\"color: white; text-decoration: none;\">" + weatherString + "</a>");
    ui->labelWeather->setToolTip(tr("Wetterdaten abgefragt: ") + weatherData.captureDateTime.toString("dd.MM.yyyy HH:mm"));
    ui->labelWeatherIcon->setText(weatherData.conditionIcon);

    qDebug() << "Weather:"
        << weatherData.captureDateTime
        << weatherData.city << weatherData.region << weatherData.country
        << weatherData.conditionString << weatherData.temperature << weatherData.temperatureUnit;
}

void MainWindow::handleWeatherUpdateFailed(QString errorString) {
    ui->labelWeather->setText(tr("Keine Wetterdaten verfügbar"));
    ui->labelWeatherIcon->setText(QString::fromUtf8("\uf07b")); // wi-na
    qWarning() << "Weather update failed:" << errorString;
}

void MainWindow::updateTime() {
    // determine current time
    QDateTime currentTime(QDateTime::currentDateTime());

    this->ui->labelTime->setText(currentTime.toString(timeFormatString));
    this->ui->labelDate->setText(currentTime.toString("dddd, d. MMMM yyyy"));
}

void MainWindow::sayTime() {
    QString textToSay = QString("Es ist " + ui->labelTime->text());
    ttsInterface->sayText(textToSay);
}

void MainWindow::loadSettings() {
    qDebug() << "Loading settings from file" << settingsFileName;

    QSettings settings(settingsFileName, QSettings::IniFormat, this);

    // load window position
    bool xRead = false;
    bool yRead = false;

    int x = settings.value("Window/x", -1).toInt(&xRead);
    int y = settings.value("Window/y", -1).toInt(&yRead);

    if (!xRead || !yRead || x < 0 || y < 0) {
        qDebug() << "Window position has been reset";
        resetWindowPosition();
    } else {
        qDebug() << "Window position loaded";
        move(x, y);
    }

    // load if seconds shall be shown
    bool displaySeconds = settings.value("displaySeconds", false).toBool();
    if (displaySeconds) {
        // set the menu entry to checked and cast event to display seconds
        showSecondsAction->setChecked(true);
    }

    // load if time announcement shall be activated
    bool timeAnnouncement = settings.value("timeAnnouncement", true).toBool();
    if (timeAnnouncement) {
        // set the menu entry to checked and cast event to activate time announcement
        sayTimePeriodicallyAction->setChecked(true);
    }

    // load weather location string
    QString locationString = settings.value("Weather/locationString", "").toString();
    weatherProvider->setLocationString(locationString);

    // load woeid
    QString woeid = settings.value("Weather/woeid", "").toString();
    weatherProvider->setWoeid(woeid);
}

void MainWindow::saveSettings() {
    QSettings settings(settingsFileName, QSettings::IniFormat, this);

    settings.setValue("Window/x", pos().x());
    settings.setValue("Window/y", pos().y());
    settings.setValue("displaySeconds", showSecondsAction->isChecked());
    settings.setValue("timeAnnouncement", sayTimePeriodicallyAction->isChecked());
    settings.setValue("Weather/locationString", weatherProvider->getLocationString());
    settings.setValue("Weather/woeid", weatherProvider->getWoeid());

    settings.sync();

    if (settings.status() != QSettings::NoError) {
        qWarning() << "Error saving the settings, error code:" << settings.status();
    }
}

void MainWindow::handleUpdatedSettings() {
    // determine if autostart entry is set to true, don't cast event when changing the GUI appearance
    autostartWithOsAction->blockSignals(true);
    autostartWithOsAction->setChecked(AutostartHelper::isAutostartActivated());
    autostartWithOsAction->blockSignals(false);
}

void MainWindow::quitProgram() {
    QApplication::quit();
}



/* ========== Helper functions ========== */

void MainWindow::setupWindowProperties() {
    // set window properties
    setWindowTitle(tr("QClockie"));

    // set window flags
    // - "FramelessWindowHint" for window without border and title bar
    // - "Tool" for window without taskbar item
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

    // TODO set Window icon

    // draw no background, keep it transparent
    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground);

    // allow tooltips on inactive window
    setAttribute(Qt::WA_AlwaysShowToolTips);
}

void MainWindow::setupWeatherIconFont() {
    // set font for the weather label
    int fontId = QFontDatabase::addApplicationFont(
        QCoreApplication::applicationDirPath() + "/assets/fonts/weathericons-regular-webfont.ttf"
    );
    if (fontId == -1) {
        // error when loading the font, show message and hide icon field
        QMessageBox::critical(
            this,
            tr("Fehler"),
            tr("Die Schriftartdatei weathericons-regular-webfont.ttf konnte nicht geladen werden, weswegen Wettersymbole nicht angezeigt werden.")
        );
        ui->labelWeatherIcon->setVisible(false);
    } else {
        // font loaded correctly
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont *weatherFont = new QFont(family, 12);
        ui->labelWeatherIcon->setFont(*weatherFont);
    }
}

void MainWindow::createMenuActions() {
    windowStaysOnTopAction = new QAction(tr("Im &Vordergrund halten"), this);
    windowStaysOnTopAction->setCheckable(true);
    connect(windowStaysOnTopAction, SIGNAL(toggled(bool)), this, SLOT(setWindowStaysOnTop(bool)));

    autostartWithOsAction = new QAction(tr("Mit &Windows starten"), this);
    autostartWithOsAction->setCheckable(true);
    connect(autostartWithOsAction, SIGNAL(toggled(bool)), this, SLOT(setAutostartOnOsStartup(bool)));

    showSecondsAction = new QAction(tr("&Sekunden anzeigen"), this);
    showSecondsAction->setCheckable(true);
    connect(showSecondsAction, SIGNAL(toggled(bool)), this, SLOT(setShowSeconds(bool)));

    showSettingsAction = new QAction(tr("&Einstellungen..."), this);
    connect(showSettingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));

    weatherAction = new QAction(tr("&Wetter aktualisieren"), this);
    connect(weatherAction, SIGNAL(triggered()), this, SLOT(updateWeather()));

    sayTimeAction = new QAction(tr("&Zeit ansagen"), this);
    sayTimeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_T));
    connect(sayTimeAction, SIGNAL(triggered()), this, SLOT(sayTime()));

    sayTimePeriodicallyAction = new QAction(tr("Zeit stündlich &ansagen"), this);
    sayTimePeriodicallyAction->setCheckable(true);
    connect(sayTimePeriodicallyAction, SIGNAL(toggled(bool)), this, SLOT(setSayTimePeriodically(bool)));

    minimizeAction = new QAction(tr("&Minimieren"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(minimizeWindow()));

    closeAction = new QAction(tr("&Beenden"), this);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(quitProgram()));
}

void MainWindow::createSystrayIcon() {
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qWarning() << "System tray is unavailable";
        return;
    }

    QString iconFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "clock.ico";
    systrayIcon = new QSystemTrayIcon(QIcon(iconFilePath), this);
    systrayIcon->setToolTip(tr("QClockie"));

    connect(
        systrayIcon,
        SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this,
        SLOT(systrayIconActivated(QSystemTrayIcon::ActivationReason))
    );

    systrayMenu = new QMenu(this);
    systrayMenu->addAction(windowStaysOnTopAction);
    systrayMenu->addSeparator();
    systrayMenu->addAction(minimizeAction);
    systrayMenu->addAction(closeAction);

    systrayIcon->setContextMenu(systrayMenu);
    systrayIcon->show();
}

void MainWindow::createWindowContextMenu() {
    windowContextMenu = new QMenu(this);

    windowContextMenu->addAction(windowStaysOnTopAction);
    windowContextMenu->addAction(autostartWithOsAction);
    windowContextMenu->addAction(showSecondsAction);
    windowContextMenu->addAction(showSettingsAction);
    windowContextMenu->addSeparator();
    windowContextMenu->addAction(weatherAction);
    windowContextMenu->addAction(sayTimeAction);
    windowContextMenu->addAction(sayTimePeriodicallyAction);
    windowContextMenu->addSeparator();
    windowContextMenu->addAction(minimizeAction);
    windowContextMenu->addAction(closeAction);
}

void MainWindow::resetWindowPosition() {
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            QApplication::desktop()->availableGeometry()
        )
    );
}
