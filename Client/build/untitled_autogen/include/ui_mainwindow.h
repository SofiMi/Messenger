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
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *leftLayout;
    QFrame *menuFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *menuButton;
    QSpacerItem *horizontalSpacer;
    QFrame *iconFind;
    QLineEdit *lineEditFind;
    QScrollArea *friendScrollArea;
    QWidget *friendScrollAreaContext;
    QVBoxLayout *rightLayout;
    QFrame *nameChatFrame;
    QScrollArea *messageScrollArea;
    QWidget *messageScrollAreaContext;
    QFrame *InputMessageFrame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 665);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
        leftLayout->setSizeConstraint(QLayout::SetFixedSize);
        menuFrame = new QFrame(centralwidget);
        menuFrame->setObjectName(QString::fromUtf8("menuFrame"));
        menuFrame->setMinimumSize(QSize(0, 45));
        menuFrame->setMaximumSize(QSize(666666, 45));
        menuFrame->setFrameShape(QFrame::StyledPanel);
        menuFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(menuFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        menuButton = new QPushButton(menuFrame);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));

        horizontalLayout->addWidget(menuButton);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        iconFind = new QFrame(menuFrame);
        iconFind->setObjectName(QString::fromUtf8("iconFind"));
        iconFind->setMinimumSize(QSize(25, 25));
        iconFind->setFrameShape(QFrame::StyledPanel);
        iconFind->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(iconFind);

        lineEditFind = new QLineEdit(menuFrame);
        lineEditFind->setObjectName(QString::fromUtf8("lineEditFind"));

        horizontalLayout->addWidget(lineEditFind);


        leftLayout->addWidget(menuFrame);

        friendScrollArea = new QScrollArea(centralwidget);
        friendScrollArea->setObjectName(QString::fromUtf8("friendScrollArea"));
        friendScrollArea->setMinimumSize(QSize(0, 0));
        friendScrollArea->setMaximumSize(QSize(300, 16777215));
        friendScrollArea->setWidgetResizable(true);
        friendScrollAreaContext = new QWidget();
        friendScrollAreaContext->setObjectName(QString::fromUtf8("friendScrollAreaContext"));
        friendScrollAreaContext->setGeometry(QRect(0, 0, 200, 68));
        friendScrollAreaContext->setMaximumSize(QSize(200, 16777215));
        friendScrollArea->setWidget(friendScrollAreaContext);

        leftLayout->addWidget(friendScrollArea, 0, Qt::AlignTop);


        horizontalLayout_2->addLayout(leftLayout);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName(QString::fromUtf8("rightLayout"));
        nameChatFrame = new QFrame(centralwidget);
        nameChatFrame->setObjectName(QString::fromUtf8("nameChatFrame"));
        nameChatFrame->setMinimumSize(QSize(0, 45));
        nameChatFrame->setMaximumSize(QSize(16777215, 45));
        nameChatFrame->setFrameShape(QFrame::StyledPanel);
        nameChatFrame->setFrameShadow(QFrame::Raised);

        rightLayout->addWidget(nameChatFrame);

        messageScrollArea = new QScrollArea(centralwidget);
        messageScrollArea->setObjectName(QString::fromUtf8("messageScrollArea"));
        messageScrollArea->setMinimumSize(QSize(500, 0));
        messageScrollArea->setWidgetResizable(true);
        messageScrollAreaContext = new QWidget();
        messageScrollAreaContext->setObjectName(QString::fromUtf8("messageScrollAreaContext"));
        messageScrollAreaContext->setGeometry(QRect(0, 0, 498, 68));
        messageScrollArea->setWidget(messageScrollAreaContext);

        rightLayout->addWidget(messageScrollArea, 0, Qt::AlignBottom);

        InputMessageFrame = new QFrame(centralwidget);
        InputMessageFrame->setObjectName(QString::fromUtf8("InputMessageFrame"));
        InputMessageFrame->setMinimumSize(QSize(0, 45));
        InputMessageFrame->setMaximumSize(QSize(16777215, 45));
        InputMessageFrame->setFrameShape(QFrame::StyledPanel);
        InputMessageFrame->setFrameShadow(QFrame::Raised);

        rightLayout->addWidget(InputMessageFrame);


        horizontalLayout_2->addLayout(rightLayout);

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
        menuButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
