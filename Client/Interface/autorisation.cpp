#include "autorisation.h"
#include "ui_autorisation.h"
#include <QDebug>
#include <QMessageBox>

Autorisation::Autorisation(QWidget *parent)
    : QWidget(parent), ui(new Ui::Autorisation) {
  ui->setupUi(this);

  setMinimumSize(400, 300);
  setMaximumSize(400, 300);

  client_ = std::make_shared<Client>();
  client_->connect("127.0.0.1", 68110);

  if (!client_->is_connected()) {
    std::cout << "No connection\n" << std::endl;
    throw;
  }
}

Autorisation::~Autorisation() { delete ui; }

void Autorisation::on_pushButton_clicked() {
  QString login = ui->login->text();
  QString password = ui->password->text();

  std::wstring login_w = login.toStdWString();
  std::wstring password_w = password.toStdWString();

  client_->CheckLogin(login_w);
  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server

  if (client_->is_connected() && !client_->get_in_comming().empty()) {
    auto msg = client_->get_in_comming().pop_front().msg;

    switch (msg.header.id) {
    case msg_type::LoginValid: {
      client_->SetUserid(msg.header.userid);
      client_->CheckPassword(password_w);

      std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server

      if (client_->is_connected() && !client_->get_in_comming().empty()) {
        auto msg_password = client_->get_in_comming().pop_front().msg;

        switch (msg_password.header.id) {
        case msg_type::PasswordValid: {
          hide();
          main_window = new MainWindow(this, client_);
          main_window->show();
          break;
        }

        case msg_type::PasswordInvalid: {
          QMessageBox::about(this, "PasswordInvalid", "PasswordInvalid");
          break;
        }

        default: {
          QMessageBox::about(this, "ServerErrord", "ServerErrord");
        }
        }
      }
      
      break;
    }
    case msg_type::LoginInvalid: {
      QMessageBox::about(this, "LoginInvalid", "LoginInvalid");
      break;
    }
    default: {
      QMessageBox::about(this, "ServerErrord", "ServerErrord");
    }
    }
  }
}
