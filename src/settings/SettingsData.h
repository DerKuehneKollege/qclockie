//
// Created by mumpi on 04.06.2016.
//

#ifndef QCLOCKIE_QCLOCKIESETTINGS_H
#define QCLOCKIE_QCLOCKIESETTINGS_H

#include <QtCore/QPoint>
#include <QtCore/QString>
#include <QtGui/QColor>

struct SettingsData {
    bool topmost;
    bool displaySeconds;
    QColor backgroundColor;
    QColor foregroundColor;
    bool timeAnnouncement;
    QString woeid;
    QString weatherLocationString;
};

#endif //QCLOCKIE_QCLOCKIESETTINGS_H
