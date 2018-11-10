//
// Created by mumpi on 16.04.2016.
//

#include "KeyboardHookWindows.h"

KeyboardHookWindows* KeyboardHookWindows::instance = NULL;

KeyboardHookWindows::KeyboardHookWindows() : QObject()
{
    // assign to null
    keyboardHook = NULL;
}

KeyboardHookWindows* KeyboardHookWindows::getInstance()
{
    if (instance == NULL) {
        instance = new KeyboardHookWindows();
    }

    return instance;
}

bool KeyboardHookWindows::isConnected()
{
    return (keyboardHook != NULL);
}

bool KeyboardHookWindows::connect()
{
    if (keyboardHook == NULL) {
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, handleKeyboardEvent, GetModuleHandle(NULL), 0);
    }

    return (keyboardHook != NULL);
}

bool KeyboardHookWindows::disconnect()
{
    bool unhookSucceeded = (bool)UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;

    return unhookSucceeded;
}

LRESULT CALLBACK KeyboardHookWindows::handleKeyboardEvent(
    int nCode,
    WPARAM wParam,
    LPARAM lParam
) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN) {
            // handle key press
            KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
            if (   pKeyboard->vkCode == 0x54 // T key
                && KeyboardHookWindows::isCtrlPressed()
                && KeyboardHookWindows::isAltPressed()
            ) {
                emit KeyboardHookWindows::getInstance()->sayTimeKeyPressed();
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

