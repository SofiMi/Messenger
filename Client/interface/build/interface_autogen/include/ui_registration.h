/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QWidget *centralwidget;
    QFrame *frameReg;
    QLabel *icon;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *name;
    QLineEdit *login;
    QLineEdit *password;
    QLineEdit *nickname;
    QPushButton *registration;
    QPushButton *to_autorization;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(700, 500);
        centralwidget = new QWidget(Registration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frameReg = new QFrame(centralwidget);
        frameReg->setObjectName(QString::fromUtf8("frameReg"));
        frameReg->setGeometry(QRect(180, 50, 341, 361));
        frameReg->setFrameShape(QFrame::StyledPanel);
        frameReg->setFrameShadow(QFrame::Raised);
        icon = new QLabel(frameReg);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setGeometry(QRect(130, 20, 90, 90));
        widget = new QWidget(frameReg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 110, 221, 151));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        name = new QLineEdit(widget);
        name->setObjectName(QString::fromUtf8("name"));

        verticalLayout->addWidget(name);

        login = new QLineEdit(widget);
        login->setObjectName(QString::fromUtf8("login"));

        verticalLayout->addWidget(login);

        password = new QLineEdit(widget);
        password->setObjectName(QString::fromUtf8("password"));

        verticalLayout->addWidget(password);

        nickname = new QLineEdit(widget);
        nickname->setObjectName(QString::fromUtf8("nickname"));

        verticalLayout->addWidget(nickname);

        registration = new QPushButton(widget);
        registration->setObjectName(QString::fromUtf8("registration"));

        verticalLayout->addWidget(registration);

        to_autorization = new QPushButton(centralwidget);
        to_autorization->setObjectName(QString::fromUtf8("to_autorization"));
        to_autorization->setGeometry(QRect(480, 10, 41, 31));
        to_autorization->setFlat(true);
        Registration->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Registration);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 22));
        Registration->setMenuBar(menubar);
        statusbar = new QStatusBar(Registration);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Registration->setStatusBar(statusbar);

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QMainWindow *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "MainWindow", nullptr));
        icon->setText(QString());
        registration->setText(QCoreApplication::translate("Registration", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        to_autorization->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
