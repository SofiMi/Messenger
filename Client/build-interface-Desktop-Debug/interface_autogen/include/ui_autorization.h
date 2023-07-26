/********************************************************************************
** Form generated from reading UI file 'autorization.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTORIZATION_H
#define UI_AUTORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_autorization
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *login_l;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *password_l;
    QLineEdit *password;
    QPushButton *to_main;
    QPushButton *to_registration;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *autorization)
    {
        if (autorization->objectName().isEmpty())
            autorization->setObjectName(QString::fromUtf8("autorization"));
        autorization->resize(419, 309);
        centralwidget = new QWidget(autorization);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(80, 50, 233, 137));
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        login_l = new QLabel(groupBox);
        login_l->setObjectName(QString::fromUtf8("login_l"));

        horizontalLayout->addWidget(login_l);

        login = new QLineEdit(groupBox);
        login->setObjectName(QString::fromUtf8("login"));

        horizontalLayout->addWidget(login);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        password_l = new QLabel(groupBox);
        password_l->setObjectName(QString::fromUtf8("password_l"));

        horizontalLayout_2->addWidget(password_l);

        password = new QLineEdit(groupBox);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout_2->addWidget(password);


        verticalLayout->addLayout(horizontalLayout_2);

        to_main = new QPushButton(groupBox);
        to_main->setObjectName(QString::fromUtf8("to_main"));

        verticalLayout->addWidget(to_main);


        verticalLayout_2->addLayout(verticalLayout);

        to_registration = new QPushButton(centralwidget);
        to_registration->setObjectName(QString::fromUtf8("to_registration"));
        to_registration->setGeometry(QRect(90, 190, 211, 21));
        to_registration->setCursor(QCursor(Qt::PointingHandCursor));
        to_registration->setAutoDefault(false);
        to_registration->setFlat(true);
        autorization->setCentralWidget(centralwidget);
        menubar = new QMenuBar(autorization);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 419, 22));
        autorization->setMenuBar(menubar);
        statusbar = new QStatusBar(autorization);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        autorization->setStatusBar(statusbar);

        retranslateUi(autorization);

        to_registration->setDefault(false);


        QMetaObject::connectSlotsByName(autorization);
    } // setupUi

    void retranslateUi(QMainWindow *autorization)
    {
        autorization->setWindowTitle(QCoreApplication::translate("autorization", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("autorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        login_l->setText(QCoreApplication::translate("autorization", " \320\233\320\276\320\263\320\270\320\275   ", nullptr));
        password_l->setText(QCoreApplication::translate("autorization", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        to_main->setText(QCoreApplication::translate("autorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        to_registration->setText(QCoreApplication::translate("autorization", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class autorization: public Ui_autorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORIZATION_H
