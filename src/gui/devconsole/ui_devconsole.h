/********************************************************************************
** Form generated from reading UI file 'devconsoleYv8204.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DEVCONSOLEYV8204_H
#define DEVCONSOLEYV8204_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DevConsoleWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *mainVerticalLayout;
    QGroupBox *devConsoleGroupBox;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *devConsoleTextEdit;
    QLineEdit *inputLineEdit;

    void setupUi(QWidget *DevConsoleWidget)
    {
        if (DevConsoleWidget->objectName().isEmpty())
            DevConsoleWidget->setObjectName(QStringLiteral("DevConsoleWidget"));
        DevConsoleWidget->resize(513, 436);
        verticalLayout_2 = new QVBoxLayout(DevConsoleWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        mainVerticalLayout = new QVBoxLayout();
        mainVerticalLayout->setObjectName(QStringLiteral("mainVerticalLayout"));
        devConsoleGroupBox = new QGroupBox(DevConsoleWidget);
        devConsoleGroupBox->setObjectName(QStringLiteral("devConsoleGroupBox"));
        verticalLayout_4 = new QVBoxLayout(devConsoleGroupBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        devConsoleTextEdit = new QTextEdit(devConsoleGroupBox);
        devConsoleTextEdit->setObjectName(QStringLiteral("devConsoleTextEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        devConsoleTextEdit->setFont(font);
        devConsoleTextEdit->setReadOnly(true);

        verticalLayout_4->addWidget(devConsoleTextEdit);

        inputLineEdit = new QLineEdit(devConsoleGroupBox);
        inputLineEdit->setObjectName(QStringLiteral("inputLineEdit"));
        inputLineEdit->setFont(font);

        verticalLayout_4->addWidget(inputLineEdit);


        mainVerticalLayout->addWidget(devConsoleGroupBox);


        verticalLayout_2->addLayout(mainVerticalLayout);


        retranslateUi(DevConsoleWidget);

        QMetaObject::connectSlotsByName(DevConsoleWidget);
    } // setupUi

    void retranslateUi(QWidget *DevConsoleWidget)
    {
        DevConsoleWidget->setWindowTitle(QApplication::translate("DevConsoleWidget", "Entwicklerkonsole", 0));
        devConsoleGroupBox->setTitle(QApplication::translate("DevConsoleWidget", "Entwicklerkonsole", 0));
        devConsoleTextEdit->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class DevConsoleWidget: public Ui_DevConsoleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DEVCONSOLEYV8204_H
