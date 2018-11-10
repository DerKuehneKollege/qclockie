//
// Created by mumpi on 01.04.2016.
//

#ifndef QCLOCKIE_AUTOSTARTHELPER_H
#define QCLOCKIE_AUTOSTARTHELPER_H

#include <QDebug>

#ifdef Q_OS_WIN
#include "AutostartHelperWindows.h"
#endif

class AutostartHelper
{
public:
    static inline bool isAutostartActivated() {
        #ifdef Q_OS_WIN
            bool autostartActivated = AutostartHelperWindows::get()->isAutostartActivated();
            qDebug() << "Windows platform detected";
            qDebug() << (autostartActivated ? "Program set to be autostarted" : "Autostart is deactivated");
            return autostartActivated;
        #elif Q_OS_UNIX
            qDebug() << "isAutostartActivated(): Unix platform detected";
            return false;
        #else
            qDebug() << "isAutostartActivated(): Unsupported platform detected";
            return false;
        #endif
    }

    static inline void setAutostartActivated() {
        #ifdef Q_OS_WIN
            qDebug() << "setAutostartActivated(): Windows platform detected";
            AutostartHelperWindows::get()->setAutostartActivated();
        #elif Q_OS_UNIX
            qDebug() << "setAutostartActivated(): Unix platform detected";
        #else
            qDebug() << "setAutostartActivated(): Unsupported platform detected";
        #endif
    }

    static inline void setAutostartDeactivated() {
        #ifdef Q_OS_WIN
            qDebug() << "setAutostartDeactivated(): Windows platform detected";
            AutostartHelperWindows::get()->setAutostartDeactivated();
        #elif Q_OS_UNIX
            qDebug() << "setAutostartDeactivated(): Unix platform detected";
        #else
            qDebug() << "setAutostartDeactivated(): Unsupported platform detected";
        #endif
    }
};

#endif //QCLOCKIE_AUTOSTARTHELPER_H
