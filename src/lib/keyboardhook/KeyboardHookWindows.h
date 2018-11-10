//
// Created by mumpi on 16.04.2016.
//

#ifndef QCLOCKIE_KEYBOARDHOOKWINDOWS_H
#define QCLOCKIE_KEYBOARDHOOKWINDOWS_H

#include <QtCore/QObject>
#include <windows.h>

class KeyboardHookWindows : public QObject
{
Q_OBJECT

public:
    // returns the current singleton instance or a new one of none existing
    static KeyboardHookWindows *getInstance();

    static inline bool isCtrlPressed() {
        return (bool)(GetAsyncKeyState(VK_CONTROL) & 0x8000);
    };

    static inline bool isAltPressed() {
        return (bool)(GetAsyncKeyState(VK_MENU) & 0x8000);
    }

    static inline bool isShiftPressed() {
        return (bool)(GetAsyncKeyState(VK_SHIFT) & 0x8000);
    }

    static inline bool isMetaPressed() {
        return (bool)(GetAsyncKeyState(VK_LWIN) & 0x8000);
    }

    bool isConnected();
    bool connect();
    bool disconnect();

signals:
    // broadcasts that a key has been pressed
    void sayTimeKeyPressed();

private:
    // constructor
    explicit KeyboardHookWindows();

    // callback function, handling keyboard input
    static LRESULT CALLBACK handleKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);

    // singleton instance
    static KeyboardHookWindows* instance;

    // instance of the Windows keyboard hook
    HHOOK keyboardHook = NULL;
};

#endif //QCLOCKIE_KEYBOARDHOOKWINDOWS_H
