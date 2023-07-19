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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *friend_scroll_area_context;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *message_scroll_area_context;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(749, 464);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setInputMethodHints(Qt::ImhNone);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        friend_scroll_area_context = new QWidget();
        friend_scroll_area_context->setObjectName(QString::fromUtf8("friend_scroll_area_context"));
        friend_scroll_area_context->setGeometry(QRect(0, 0, 343, 68));
        scrollArea->setWidget(friend_scroll_area_context);

        horizontalLayout_2->addWidget(scrollArea, 0, Qt::AlignTop);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        scrollArea_2 = new QScrollArea(widget_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        message_scroll_area_context = new QWidget();
        message_scroll_area_context->setObjectName(QString::fromUtf8("message_scroll_area_context"));
        message_scroll_area_context->setGeometry(QRect(0, 0, 342, 68));
        scrollArea_2->setWidget(message_scroll_area_context);

        horizontalLayout_3->addWidget(scrollArea_2, 0, Qt::AlignBottom);


        horizontalLayout->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Messenger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
