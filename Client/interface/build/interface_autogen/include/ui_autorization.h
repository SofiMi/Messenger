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

class Ui_autorization
{
public:
    QWidget *centralwidget;
    QFrame *checkframe;
    QWidget *layoutWidget;
    QVBoxLayout *layout;
    QLineEdit *login;
    QLineEdit *password;
    QPushButton *to_main;
    QFrame *frame;
    QLabel *icon;
    QPushButton *to_registration;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *autorization)
    {
        if (autorization->objectName().isEmpty())
            autorization->setObjectName(QString::fromUtf8("autorization"));
        autorization->resize(700, 500);
        centralwidget = new QWidget(autorization);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        checkframe = new QFrame(centralwidget);
        checkframe->setObjectName(QString::fromUtf8("checkframe"));
        checkframe->setGeometry(QRect(30, 110, 191, 91));
        checkframe->setFrameShape(QFrame::StyledPanel);
        checkframe->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(checkframe);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 191, 105));
        layout = new QVBoxLayout(layoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setContentsMargins(0, 0, 0, 0);
        login = new QLineEdit(layoutWidget);
        login->setObjectName(QString::fromUtf8("login"));

        layout->addWidget(login);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        layout->addWidget(password);

        to_main = new QPushButton(layoutWidget);
        to_main->setObjectName(QString::fromUtf8("to_main"));

        layout->addWidget(to_main);

        frame = new QFrame(layoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        layout->addWidget(frame);

        icon = new QLabel(centralwidget);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setGeometry(QRect(90, 50, 61, 51));
        to_registration = new QPushButton(centralwidget);
        to_registration->setObjectName(QString::fromUtf8("to_registration"));
        to_registration->setGeometry(QRect(30, 200, 189, 25));
        to_registration->setCursor(QCursor(Qt::PointingHandCursor));
        to_registration->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0.505682, x2:1, y2:0.477, stop:0 rgba(20, 67, 78, 219), stop:1 rgba(105, 118, 132, 226));\\n\"\n"
"                                                \"color:rgba(255, 255, 255, 210);\\n\"\n"
"                                                \"border-radius:5px;\\n\"}"));
        to_registration->setIconSize(QSize(16, 15));
        to_registration->setAutoDefault(false);
        to_registration->setFlat(true);
        autorization->setCentralWidget(centralwidget);
        menubar = new QMenuBar(autorization);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 22));
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
        to_main->setText(QCoreApplication::translate("autorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        icon->setText(QString());
        to_registration->setText(QCoreApplication::translate("autorization", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class autorization: public Ui_autorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORIZATION_H
