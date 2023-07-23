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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QScrollArea *friendScrollArea;
    QWidget *friendScrollAreaContext;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QScrollArea *messageScrollArea;
    QWidget *messageScrollAreaContext;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *InputMsg;
    QPushButton *SendMsg;
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
        layoutWidget->setGeometry(QRect(20, 10, 251, 521));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(layoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 45));
        frame->setMaximumSize(QSize(16777215, 45));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        friendScrollArea = new QScrollArea(layoutWidget);
        friendScrollArea->setObjectName(QString::fromUtf8("friendScrollArea"));
        friendScrollArea->setWidgetResizable(true);
        friendScrollAreaContext = new QWidget();
        friendScrollAreaContext->setObjectName(QString::fromUtf8("friendScrollAreaContext"));
        friendScrollAreaContext->setGeometry(QRect(0, 0, 247, 68));
        friendScrollArea->setWidget(friendScrollAreaContext);

        verticalLayout->addWidget(friendScrollArea, 0, Qt::AlignTop);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(280, 10, 491, 521));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(layoutWidget1);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 45));
        frame_2->setMaximumSize(QSize(16777215, 45));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame_2);

        messageScrollArea = new QScrollArea(layoutWidget1);
        messageScrollArea->setObjectName(QString::fromUtf8("messageScrollArea"));
        messageScrollArea->setWidgetResizable(true);
        messageScrollAreaContext = new QWidget();
        messageScrollAreaContext->setObjectName(QString::fromUtf8("messageScrollAreaContext"));
        messageScrollAreaContext->setGeometry(QRect(0, 0, 487, 413));
        messageScrollArea->setWidget(messageScrollAreaContext);

        verticalLayout_3->addWidget(messageScrollArea);

        frame_3 = new QFrame(layoutWidget1);
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
