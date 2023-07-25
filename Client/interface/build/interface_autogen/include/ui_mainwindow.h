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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QScrollArea *messageScrollArea;
    QWidget *messageScrollAreaContext;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *InputMsg;
    QPushButton *SendMsg;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *findNick;
    QLineEdit *inputNick;
    QScrollArea *friendScrollArea;
    QWidget *friendScrollAreaContext;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(280, 10, 491, 521));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 45));
        frame_2->setMaximumSize(QSize(16777215, 45));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame_2);

        messageScrollArea = new QScrollArea(layoutWidget);
        messageScrollArea->setObjectName(QString::fromUtf8("messageScrollArea"));
        messageScrollArea->setWidgetResizable(true);
        messageScrollAreaContext = new QWidget();
        messageScrollAreaContext->setObjectName(QString::fromUtf8("messageScrollAreaContext"));
        messageScrollAreaContext->setGeometry(QRect(0, 0, 487, 413));
        messageScrollArea->setWidget(messageScrollAreaContext);

        verticalLayout_3->addWidget(messageScrollArea);

        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 45));
        frame_3->setMaximumSize(QSize(16777215, 16777215));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        InputMsg = new QLineEdit(frame_3);
        InputMsg->setObjectName(QString::fromUtf8("InputMsg"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InputMsg->sizePolicy().hasHeightForWidth());
        InputMsg->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(InputMsg);

        SendMsg = new QPushButton(frame_3);
        SendMsg->setObjectName(QString::fromUtf8("SendMsg"));

        horizontalLayout->addWidget(SendMsg);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(frame_3, 0, Qt::AlignTop);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 261, 511));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 45));
        frame->setMaximumSize(QSize(16777215, 45));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        findNick = new QPushButton(frame);
        findNick->setObjectName(QString::fromUtf8("findNick"));

        horizontalLayout_2->addWidget(findNick);

        inputNick = new QLineEdit(frame);
        inputNick->setObjectName(QString::fromUtf8("inputNick"));

        horizontalLayout_2->addWidget(inputNick);


        verticalLayout->addWidget(frame);

        friendScrollArea = new QScrollArea(widget);
        friendScrollArea->setObjectName(QString::fromUtf8("friendScrollArea"));
        friendScrollArea->setWidgetResizable(true);
        friendScrollAreaContext = new QWidget();
        friendScrollAreaContext->setObjectName(QString::fromUtf8("friendScrollAreaContext"));
        friendScrollAreaContext->setGeometry(QRect(0, 0, 257, 456));
        friendScrollArea->setWidget(friendScrollAreaContext);

        verticalLayout->addWidget(friendScrollArea);

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
        SendMsg->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QString());
        findNick->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
