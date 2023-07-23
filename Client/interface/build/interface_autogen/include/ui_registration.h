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

class Ui_Registration
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *name;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *password;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *nickname;
    QPushButton *pushButton;
    QPushButton *to_autorization;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(445, 404);
        centralwidget = new QWidget(Registration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(70, 50, 301, 241));
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        name = new QLineEdit(groupBox);
        name->setObjectName(QString::fromUtf8("name"));

        horizontalLayout_4->addWidget(name);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        login = new QLineEdit(groupBox);
        login->setObjectName(QString::fromUtf8("login"));

        horizontalLayout_3->addWidget(login);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        password = new QLineEdit(groupBox);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout_2->addWidget(password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        nickname = new QLineEdit(groupBox);
        nickname->setObjectName(QString::fromUtf8("nickname"));

        horizontalLayout->addWidget(nickname);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout_5->addLayout(verticalLayout);

        to_autorization = new QPushButton(centralwidget);
        to_autorization->setObjectName(QString::fromUtf8("to_autorization"));
        to_autorization->setGeometry(QRect(390, 10, 41, 31));
        Registration->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Registration);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 445, 22));
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
        groupBox->setTitle(QCoreApplication::translate("Registration", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("Registration", "\320\230\320\274\321\217:         ", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "\320\233\320\276\320\263\320\270\320\275:     ", nullptr));
        label_3->setText(QCoreApplication::translate("Registration", "\320\237\320\260\321\200\320\276\320\273\321\214:  ", nullptr));
        label_4->setText(QCoreApplication::translate("Registration", "\320\235\320\270\320\272:         ", nullptr));
        pushButton->setText(QCoreApplication::translate("Registration", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        to_autorization->setText(QCoreApplication::translate("Registration", "<--", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
