#include "registration.h"
#include "mainwindow.h"
#include "ui_registration.h"
#include "autorization.h"
#include <QMessageBox>

Registration::Registration(QWidget* parent, std::shared_ptr<Client>& client) :
  QMainWindow(parent),
  ui(new Ui::Registration),
  client_(client) {
  ui->setupUi(this);
  add_style();
}

Registration::~Registration() { delete ui; }

void Registration::on_pushButton_clicked() {
  std::string login = ui->login->text().toStdString();
  std::string password = ui->password->text().toStdString();
  std::string name = ui->name->text().toStdString();
  std::string nickname = ui->nickname->text().toStdString();
  std::vector<std::string> user_info = { login, password, name, nickname };

  if (login.size() == 0 || password.size() == 0 || name.size() == 0 || nickname.size() == 0) {
    QMessageBox::about(this, "Ошибка регистрации", "Необходимо заполнить все поля.");
    return;
  }

  if (login.size() > 50 || password.size() > 50 || name.size() > 50 || nickname.size() > 50) {
    QMessageBox::about(this, "Ошибка регистрации", "Максимальная длина вводимых данных составляет 50 символов.");
    return;
  }

  if (!client_->CheckUniqueLogin(login)) {
    QMessageBox::about(this, "Ошибка регистрации", "Логин не уникальный. Попробуйте другой. ");
    return;
  }

  if (!client_->CheckUniqueNickname(nickname)) {
    QMessageBox::about(this, "Ошибка регистрации", "Никнейм не уникальный. Попробуйте другой.");
    return;
  }

  client_->AddNewUser(user_info);
  hide();
  MainWindow* mainwindow = new MainWindow(this, client_);
  mainwindow->show();
}


void Registration::on_to_autorization_clicked() {
  hide();
  autorization* mainwindow = new autorization(this, client_);
  mainwindow->show();
}

void Registration::add_style() {
  QPixmap bkgnd("../../../Asserts/bg_reg.jpg");
  bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
  QPalette p = palette();
  p.setBrush(QPalette::Background, bkgnd);
  setPalette(p);


   ui->frameReg->setStyleSheet(  "QFrame {background-color: rgba(255, 255, 255, 200);}\n"
                                  "QLineEdit {background-color: rgba(0, 0, 0, 0);\n"
                                             "border:none;\n"
                                             "border-bottom: 2px solid rgba(21,24,60,255);\n"
                                             "padding-bottom: 7px;}\n"
                                  "QPushButton {background-color: qlineargradient(spread:pad, x1:0, y1:0.505682, x2:1, y2:0.477, stop:0 rgba(21,24,60,255), stop:1 rgba(61,177,221,255));\n"
                                                "color:rgba(255, 255, 255, 210);\n"
                                                "border-radius:2px;\n"
                                  "}\n"
                                  "QPushButton:hover {background-color: qlineargradient(spread:pad, x1:0, y1:0.505682, x2:1, y2:0.477, stop:0 rgba(61,177,221,255), stop:1 rgba(21,24,60,255));\n"
                                                      "cursor: pointer;"
                                  "}\n"
                                  "QPushButton:pressed {background-color:rgba(105, 118, 132, 200)\n"
                                                       "color:rgba(255, 255, 255, 210);\n"
                                                       "border-radius:5px;\n"
                                                       "padding-left:5px;\n"
                                  "}\n"
                                 );
  ui->password->setPlaceholderText("Пароль");
  ui->login->setPlaceholderText("Логин");
  ui->name->setPlaceholderText("Имя");
  ui->nickname->setPlaceholderText("@nickname");

  QPixmap icon("../../../Asserts/icon2.png");
  ui->icon->setPixmap(icon);
  ui->icon->setStyleSheet("QLabel {background-color: rgba(0, 0, 0, 0);}");

  QPixmap before("../../../Asserts/before.png");
  QIcon button_icon(before);
  ui->to_autorization->setIcon(button_icon);
  ui->to_autorization->setIconSize(QSize(35, 35));

  ui->to_autorization->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
  ui->registration->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
}

