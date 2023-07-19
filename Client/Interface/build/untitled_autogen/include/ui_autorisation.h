/********************************************************************************
** Form generated from reading UI file 'autorisation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTORISATION_H
#define UI_AUTORISATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Autorisation
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *login_lavel;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *password_label;
    QLineEdit *password;
    QPushButton *pushButton;

    void setupUi(QWidget *Autorisation)
    {
        if (Autorisation->objectName().isEmpty())
            Autorisation->setObjectName(QString::fromUtf8("Autorisation"));
        Autorisation->resize(400, 300);
        groupBox = new QGroupBox(Autorisation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(60, 70, 261, 151));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 219, 95));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        login_lavel = new QLabel(layoutWidget);
        login_lavel->setObjectName(QString::fromUtf8("login_lavel"));

        horizontalLayout->addWidget(login_lavel);

        login = new QLineEdit(layoutWidget);
        login->setObjectName(QString::fromUtf8("login"));

        horizontalLayout->addWidget(login);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        password_label = new QLabel(layoutWidget);
        password_label->setObjectName(QString::fromUtf8("password_label"));

        horizontalLayout_2->addWidget(password_label);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout_2->addWidget(password);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(Autorisation);

        QMetaObject::connectSlotsByName(Autorisation);
    } // setupUi

    void retranslateUi(QWidget *Autorisation)
    {
        Autorisation->setWindowTitle(QCoreApplication::translate("Autorisation", "Messanger", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Autorisation", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        login_lavel->setText(QCoreApplication::translate("Autorisation", "login", nullptr));
        password_label->setText(QCoreApplication::translate("Autorisation", "password", nullptr));
        pushButton->setText(QCoreApplication::translate("Autorisation", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Autorisation: public Ui_Autorisation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORISATION_H
