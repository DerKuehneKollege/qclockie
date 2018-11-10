//
// Created by mumpi on 03.04.2016.
//
// TODO: https://gist.github.com/Youka/365dc146c14d10ea9659

#include <QtCore/QStringList>

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
    QString program = "WindowsSapi.exe";

    QStringList arguments;
    arguments << "/say";
    arguments << "\"" + text + "\"";

    qDebug() << "Text to speech utterance:" << text;
    ttsProcess->start(program, arguments);
}
