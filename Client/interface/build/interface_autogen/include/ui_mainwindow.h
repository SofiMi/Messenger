/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QScrollArea *friendScrollArea;
    QWidget *friendScrollAreaContext;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QScrollArea *messageScrollArea;
    QWidget *messageScrollAreaContext;
    QFrame *frame_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 10, 251, 521));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 45));
        frame->setMaximumSize(QSize(16777215, 45));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        friendScrollArea = new QScrollArea(widget);
        friendScrollArea->setObjectName(QString::fromUtf8("friendScrollArea"));
        friendScrollArea->setWidgetResizable(true);
        friendScrollAreaContext = new QWidget();
        friendScrollAreaContext->setObjectName(QString::fromUtf8("friendScrollAreaContext"));
        friendScrollAreaContext->setGeometry(QRect(0, 0, 247, 68));
        friendScrollArea->setWidget(friendScrollAreaContext);

        verticalLayout->addWidget(friendScrollArea, 0, Qt::AlignTop);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(280, 10, 511, 521));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(widget1);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 45));
        frame_2->setMaximumSize(QSize(16777215, 45));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame_2);

        messageScrollArea = new QScrollArea(widget1);
        messageScrollArea->setObjectName(QString::fromUtf8("messageScrollArea"));
        messageScrollArea->setWidgetResizable(true);
        messageScrollAreaContext = new QWidget();
        messageScrollAreaContext->setObjectName(QString::fromUtf8("messageScrollAreaContext"));
        messageScrollAreaContext->setGeometry(QRect(0, 0, 507, 415));
        messageScrollArea->setWidget(messageScrollAreaContext);

        verticalLayout_3->addWidget(messageScrollArea);

        frame_3 = new QFrame(widget1);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 45));
        frame_3->setMaximumSize(QSize(16777215, 45));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
