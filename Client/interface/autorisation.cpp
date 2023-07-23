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
  client_->connect("127.0.0.1", 10007);

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
    std::string error_message;

    if (client_->Autorization(login_w, password_w, error_message)) {
      hide();
      main_window = new MainWindow(this, client_);
      main_window->show();
    } else {
      std::cout << error_message << std::endl;
    }
}

