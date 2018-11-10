//
// Created by mumpi on 24.04.2016.
//

#include <QtCore/QDebug>
#include <QtWidgets/QStyle>
#include <QtWidgets/QDesktopWidget>

#include "DevConsoleWidget.h"
#include "../../weather/YahooWeatherProvider.h"

DevConsoleWidget::DevConsoleWidget(QWidget *parent) : QWidget(parent), ui(new Ui::DevConsoleWidget) {
    ui->setupUi(this);

    // center window
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );

    // pressing return in input line edit submits command
    connect(ui->inputLineEdit, SIGNAL(returnPressed()), this, SLOT(commandSubmitted()));

    weatherProvider = nullptr;
}

DevConsoleWidget::~DevConsoleWidget() {
    delete ui;
}

void DevConsoleWidget::logMessage(const QString &msg) {
    ui->devConsoleTextEdit->append(msg);
}

/* ========== SLOTs ========== */

void DevConsoleWidget::keyPressEvent(QKeyEvent *keyEvent) {
    if (keyEvent->key() == Qt::Key_F12) {
        qDebug() << "F12 pressed, debug window is hidden";
        keyEvent->accept();

        hide();
    } else {
        // further propagate event
        QWidget::keyPressEvent(keyEvent);
    }
}

void DevConsoleWidget::commandSubmitted() {
    // TODO add comands to be interpreted
    QString command = ui->inputLineEdit->text();
    qDebug() << "Entered:" << command;
    ui->inputLineEdit->clear();

    if (command.startsWith("search_location ")) {
        QString location = command.remove("search_location ");
        if (weatherProvider == nullptr) {
            weatherProvider = new YahooWeatherProvider();
        }
        weatherProvider->sendSearchLocationRequest(location);
    }
}
