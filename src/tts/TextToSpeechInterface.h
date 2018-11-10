//
// Created by mumpi on 03.04.2016.
//

#ifndef QCLOCKIE_TTSINTERFACE_H
#define QCLOCKIE_TTSINTERFACE_H

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QProcess>

class TextToSpeechInterface : public QObject {
    Q_OBJECT

public:
    TextToSpeechInterface(QObject *parent);
    void sayText(QString text);

private slots:
    void ttsStarted();
    void ttsFinished(int exitCode);
    void ttsErrorOccurred(QProcess::ProcessError error);

private:
    QProcess *ttsProcess;
};


#endif //QCLOCKIE_TTSINTERFACE_H
