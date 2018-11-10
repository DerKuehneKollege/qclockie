//
// Created by mumpi on 01.04.2016.
//

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "AutostartHelperWindows.h"

AutostartHelperWindows* AutostartHelperWindows::instance = 0;

AutostartHelperWindows *AutostartHelperWindows::get() {
    if (!AutostartHelperWindows::instance) {
        AutostartHelperWindows::instance = new AutostartHelperWindows();
    }

    return AutostartHelperWindows::instance;
}

AutostartHelperWindows::AutostartHelperWindows() {
    settings = new QSettings(
        QStringLiteral("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
        QSettings::NativeFormat
    );
}

AutostartHelperWindows::~AutostartHelperWindows() { }

bool AutostartHelperWindows::isAutostartActivated() {
    // TODO check if the registry value contains a valid path
    // QString regValue = settings->value(QStringLiteral("QClockie")).toString();

    return settings->contains(QStringLiteral("QClockie"));
}

void AutostartHelperWindows::setAutostartActivated() {
    // determine application file path automatically
    QString applicationFilePath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    QString regValue = QString("\"" + applicationFilePath + "\" /autostart");

    settings->setValue(
        QStringLiteral("QClockie"),
        regValue
    );

    qDebug() << "Added key value:" << regValue;
}

void AutostartHelperWindows::setAutostartDeactivated() {
    settings->remove(QStringLiteral("QClockie"));
    qDebug() << "Removed key value";
}











