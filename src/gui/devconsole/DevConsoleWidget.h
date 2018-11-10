//
// Created by mumpi on 24.04.2016.
//

#ifndef QCLOCKIE_DEVCONSOLEWIDGET_H
#define QCLOCKIE_DEVCONSOLEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QKeyEvent>

#include "ui_devconsole.h"
#include "../../weather/YahooWeatherProvider.h"

namespace Ui {
    class DevConsoleWidget;
}

class DevConsoleWidget : public QWidget {
Q_OBJECT

public:
    explicit DevConsoleWidget(QWidget *parent = 0);
    ~DevConsoleWidget();
    void logMessage(const QString &msg);

private slots:
    void keyPressEvent(QKeyEvent* keyEvent);
    void commandSubmitted();

private:
    Ui::DevConsoleWidget *ui;
    YahooWeatherProvider *weatherProvider;
};


#endif //QCLOCKIE_DEVCONSOLEWIDGET_H
