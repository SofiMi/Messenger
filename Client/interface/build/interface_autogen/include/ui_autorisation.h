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

class Ui_autorisation
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *login_l;
    QLineEdit *login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *password_l;
    QLineEdit *password;
    QPushButton *pushButton;

    void setupUi(QWidget *autorisation)
    {
        if (autorisation->objectName().isEmpty())
            autorisation->setObjectName(QString::fromUtf8("autorisation"));
        autorisation->resize(388, 282);
        groupBox = new QGroupBox(autorisation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(80, 60, 233, 137));
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

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(autorisation);

        QMetaObject::connectSlotsByName(autorisation);
    } // setupUi

    void retranslateUi(QWidget *autorisation)
    {
        autorisation->setWindowTitle(QCoreApplication::translate("autorisation", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("autorisation", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        login_l->setText(QCoreApplication::translate("autorisation", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        password_l->setText(QCoreApplication::translate("autorisation", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        pushButton->setText(QCoreApplication::translate("autorisation", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class autorisation: public Ui_autorisation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORISATION_H
