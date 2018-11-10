//
// Created by mumpi on 03.04.2016.
//
// TODO: https://gist.github.com/Youka/365dc146c14d10ea9659

#include <QtCore/QStringList>
#include <windows.h>
#include <sapi.h>

#include "TextToSpeechInterface.h"

TextToSpeechInterface::TextToSpeechInterface(QObject *parent) {
    ttsProcess = new QProcess(parent);

    connect(ttsProcess, SIGNAL(started()), this, SLOT(ttsStarted()));
    connect(ttsProcess, SIGNAL(finished(int)), this, SLOT(ttsFinished(int)));
    connect(ttsProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(ttsErrorOccurred(QProcess::ProcessError)));
}

void TextToSpeechInterface::ttsStarted() {
    qDebug() << "TTS process started";
}

void TextToSpeechInterface::ttsFinished(int exitCode) {
    qDebug() << "TTS process finished with exit code" << exitCode;
}

void TextToSpeechInterface::ttsErrorOccurred(QProcess::ProcessError error) {
    qDebug() << "Error occurred executing TTS process, code" << error;
}

void TextToSpeechInterface::sayText(QString text) {
    ISpVoice * pVoice = NULL;

    if (FAILED(::CoInitialize(NULL))) {
        return;
    }

    LPCWSTR textWchar = (const wchar_t*) text.utf16();

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if (SUCCEEDED(hr)) {
        hr = pVoice->Speak(textWchar, 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    ::CoUninitialize();

    qDebug() << "Text to speech utterance:" << text;
}









