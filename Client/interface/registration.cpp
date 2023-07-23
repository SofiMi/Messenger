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

