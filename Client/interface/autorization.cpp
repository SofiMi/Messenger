#include "autorization.h"
#include "ui_autorization.h"
#include "registration.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QPixmap>
#include <QPalette>

autorization::autorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::autorization)
{
    ui->setupUi(this);

    client_ = std::make_shared<Client>();
    client_->connect("127.0.0.1", 10000);

    if (!client_->is_connected()) {
      std::cout << "No connection\n" << std::endl;
      throw;
    }

    add_style();
}

autorization::autorization(QWidget* parent, std::shared_ptr<Client> client):
    QMainWindow(parent), ui(new Ui::autorization), client_(client)
{
    ui->setupUi(this);
    add_style();
}

autorization::~autorization()
{
    delete ui;
}

void autorization::on_to_main_clicked() {
    QString login = ui->login->text();
    QString password = ui->password->text();

    std::string login_w = login.toStdString();
    std::string password_w = password.toStdString();
    std::string error_message;

    if (client_->Autorization(login_w, password_w, error_message)) {
      hide();
      main_window = new MainWindow(this, client_);
      main_window->show();
    } else {
      QMessageBox::about(this, "Ошибка авторизации", error_message.c_str());
    }
}


void autorization::on_to_registration_clicked()
{
    hide();
    Registration* m = new Registration(this, client_);
    m->show();
}

void autorization::add_style() {
    QPixmap bkgnd("../../../Asserts/login.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->checkframe->setStyleSheet("QFrame {background-color: rgba(0, 0, 0, 0);}\n"
                                  "QLineEdit {background-color: rgba(0, 0, 0, 0);\n"
                                             "border:none;\n"
                                             "border-bottom: 2px solid rgba(105, 118, 132, 255);\n"
                                             "padding-bottom: 7px;}\n"
                                  "QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:0.505682, x2:1, y2:0.477, stop:0 rgba(20, 67, 78, 219), stop:1 rgba(105, 118, 132, 226));\n"
                                                "color:rgba(255, 255, 255, 210);\n"
                                                "border-radius:4px;\n"
                                  "}\n"
                                  "QPushButton:hover {background-color: qlineargradient(spread:pad, x1:0, y1:0.505682, x2:1, y2:0.477, stop:0 rgba(20, 47, 78, 219), stop:1 rgba(85, 98, 112, 226));\n"
                                  "}\n"
                                  "QPushButton:pressed {background-color:rgba(105, 118, 132, 200)\n"
                                                       "color:rgba(255, 255, 255, 210);\n"
                                                       "border-radius:5px;\n"
                                                       "padding-left:5px;\n"
                                  "}\n"
                                 );
    ui->password->setPlaceholderText("Пароль");
    ui->login->setPlaceholderText("Логин");

    QPixmap icon("../../../Asserts/icon1.png");
    //icon = icon.scaled(QSize(60, 60), Qt::IgnoreAspectRatio);
    ui->icon->setPixmap(icon);
}