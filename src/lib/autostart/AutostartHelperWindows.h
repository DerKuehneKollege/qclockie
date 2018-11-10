//
// Created by mumpi on 01.04.2016.
//

#ifndef QCLOCKIE_AUTOSTARTHELPERWINDOWS_H
#define QCLOCKIE_AUTOSTARTHELPERWINDOWS_H

#include <QtCore/QSettings>

class AutostartHelperWindows {
public:
    static AutostartHelperWindows* get();

    bool isAutostartActivated();
    void setAutostartActivated();
    void setAutostartDeactivated();

private:
    static AutostartHelperWindows* instance;

    AutostartHelperWindows();
    ~AutostartHelperWindows();

    QSettings *settings;
};


#endif //QCLOCKIE_AUTOSTARTHELPERWINDOWS_H
