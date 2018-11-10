//
// Created by mumpi on 09.04.2016.
//

#ifndef QCLOCKIE_TIMEANNOUNCEMENT_H
#define QCLOCKIE_TIMEANNOUNCEMENT_H


#include <QtCore/QObject>
#include <QtCore/QTimer>
#include "TextToSpeechInterface.h"

class TimeAnnouncement : public QObject {
    Q_OBJECT

public:
    TimeAnnouncement();
    ~TimeAnnouncement();
    void startFullHourTimeAnnouncement();
    void stopTimeAnnouncement();

private slots:
    void reactToNextFullHourReached();

signals:
    void nextFullHourReached();

private:
    QTimer *timer;
};


#endif //QCLOCKIE_TIMEANNOUNCEMENT_H
