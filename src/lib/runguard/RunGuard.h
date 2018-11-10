//
// Created by mumpi on 09.04.2016.
// from: http://stackoverflow.com/a/28172162
//
// Allows to check if an application is already running.
//

#ifndef RUNGUARD_H
#define RUNGUARD_H

#include <QtCore/QObject>
#include <QtCore/QSharedMemory>
#include <QtCore/QSystemSemaphore>

class RunGuard {
public:
    RunGuard(const QString &key);
    ~RunGuard();
    bool isAnotherRunning();
    bool tryToRun();
    void release();

private:
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;

    Q_DISABLE_COPY(RunGuard)
};


#endif // RUNGUARD_H
