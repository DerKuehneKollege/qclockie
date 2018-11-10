#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDateTime>

#include "version_number.h"
#include "gui/MainWindow.h"
#include "lib/runguard/RunGuard.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // catch qDebug output und forward them to the developer console
    QString currentDateTimeString = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString localMsg;
    switch (type) {
        case QtDebugMsg:
            localMsg = QString("[%1] [DEBUG] %2").arg(currentDateTimeString, msg);
            break;
        case QtInfoMsg:
            localMsg = QString("[%1] [INFO] %2").arg(currentDateTimeString, msg);
            break;
        case QtWarningMsg:
            localMsg = QString("[%1] [WARN] %2").arg(currentDateTimeString, msg);
            break;
        case QtCriticalMsg:
            localMsg = QString("[%1] [CRIT] %2").arg(currentDateTimeString, msg);
            break;
        case QtFatalMsg:
            localMsg = QString("[%1] [FATAL] %2").arg(currentDateTimeString, msg);
            printf(localMsg.append("\n").toLocal8Bit().constData());
            abort();
    }

    if (MainWindow::devConsoleWidget != nullptr) {
        MainWindow::devConsoleWidget->logMessage(localMsg);
    }

    printf(localMsg.append("\n").toLocal8Bit().constData());
}

int main(int argc, char *argv[])
{
    // run QClockie only one, it is not meaningful to run it multiple times
    RunGuard singleInstanceApplicationGuard("QClockie");

    // catch qDebug output und forward them to the developer console
    qInstallMessageHandler(myMessageOutput);

    QApplication qClockieApp(argc, argv);

    // set application information
    qClockieApp.setOrganizationName("Atomkraftzwerg");
    qClockieApp.setOrganizationDomain("atomkraftzwerg.de");
    qClockieApp.setApplicationName("QClockie");

    // set version number, use version number provided by cmake
    QVersionNumber versionNumber(QCLOCKIE_VERSION_MAJOR, QCLOCKIE_VERSION_MINOR, QCLOCKIE_VERSION_REVISION);
    QCoreApplication::setApplicationVersion(versionNumber.toString());

    // do not close the whole application if e.g. only the settings dialog is closed
    qClockieApp.setQuitOnLastWindowClosed(false);

    // set scaling factor of the application to one
    // TODO implement solution for higher DPI monitors
    QProcessEnvironment::systemEnvironment().insert("QT_SCALE_FACTOR", "1");

    // print program version to console
    qInfo() << QString("Running %1 v%2")
                   .arg(QCoreApplication::applicationName())
                   .arg(QCoreApplication::applicationVersion());

    // prevent running the application twice
    if (!singleInstanceApplicationGuard.tryToRun()) {
        qDebug() << "There is already a running instance of QClockie.";
        QMessageBox::information(
            nullptr,
            QObject::tr("Information"),
            QObject::tr("Es ist bereits eine andere Instanz der Anwendung geöffnet.")
        );
        return 0;
    }

    // run the application as usual
    MainWindow w;
    w.show();

    return qClockieApp.exec();
}
