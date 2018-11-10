//
// Created by mumpi on 09.04.2016.
//

#include <QtCore/QTime>
#include "TimeAnnouncement.h"

TimeAnnouncement::TimeAnnouncement() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reactToNextFullHourReached()));
}

TimeAnnouncement::~TimeAnnouncement() {
    if (timer != nullptr) {
        if (timer->isActive()) {
            timer->stop();
        }
        delete timer;
    }
}

void TimeAnnouncement::startFullHourTimeAnnouncement() {
    // calculate seconds until next full hour
    QTime now = QTime::currentTime();
    int msecsUntilNextFullHour = (3600000) - now.msecsSinceStartOfDay() % (3600000);
    qDebug() << "Next time announcement in" << msecsUntilNextFullHour / 1000 / 60 << "minutes";

    // start timer that fires when the next hour is reached, add one second just to be sure
    timer->start(msecsUntilNextFullHour + 1000);
}

void TimeAnnouncement::stopTimeAnnouncement() {
    if (timer->isActive()) {
        timer->stop();
    }
}

void TimeAnnouncement::reactToNextFullHourReached() {
    QTime now = QTime::currentTime();

    // check if the time has really reached a full hour (minute == 0),
    // could be that the timer interval became wrong due to sending the OS to sleep mode etc.
    if (now.minute() != 0) {
        // if that is the case do not emit nextFullHourReached event, but restart the timer
        qDebug() << "Restarting timer, next full hour not reached:" << now.toString("HH:mm:ss");
        startFullHourTimeAnnouncement();
        return;
    }

    // expect that this was fired at a full hour, thus the next full hour is expected to be in 1h
    timer->start(3600000);

    // handle reaction
    qDebug() << "Next full hour reached:" << now.toString("HH:mm:ss");
    emit nextFullHourReached();
}
