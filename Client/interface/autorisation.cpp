#include "autorisation.h"
#include "ui_autorisation.h"
#include <QDebug>
#include <QMessageBox>

autorisation::autorisation(QWidget *parent)
    : QWidget(parent), ui(new Ui::autorisation) {
  ui->setupUi(this);

  setMinimumSize(400, 300);
  setMaximumSize(400, 300);

  client_ = std::make_shared<Client>();
  client_->connect("127.0.0.1", 65000);

  if (!client_->is_connected()) {
    std::cout << "No connection\n" << std::endl;
    throw;
  }
}

autorisation::~autorisation() { delete ui; }

void autorisation::on_pushButton_clicked() {
    QString login = ui->login->text();
    QString password = ui->password->text();

    std::string login_w = login.toStdString();
    std::string password_w = password.toStdString();

    client_->CheckLogin(login_w);
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server

    if (client_->is_connected() && !client_->get_in_comming().empty()) {
      auto msg = client_->get_in_comming().pop_front().msg;

      switch (msg.header.id) {
        case msg_type::ServerAccept: {
          std::cout << "ServerAccept" << std::endl;
        }
        case msg_type::LoginValid: {
          int userid;
          std::copy(reinterpret_cast<int*>(&msg.data[0]), reinterpret_cast<int*>(&msg.data[0] + sizeof(int)), &userid);
          client_->SetUserid(userid);
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
              QMessageBox::about(this, "ServerErrord in Password", "ServerErrord in Password");
            }
            }
          }

          break;
        }
        case msg_type::LoginInvalid: {
          QMessageBox::about(this, "LoginInvalid", "LoginInvalid");
          break;
        }
        case msg_type::PasswordValid: {
          QMessageBox::about(this, "ServerErrord: PV", "ServerErrord : PV");
          break;
        }
        case msg_type::PasswordInvalid: {
          QMessageBox::about(this, "ERROR:PasswordInvalid", "ERROR:PasswordInvalid");
          break;
        }
        default: {
          QMessageBox::about(this, "ServerErrord", "ServerErrord");
        }
      }
    } else {
      std::cout << "empty" << std::endl;
    }
}

