#include "autorization.h"
#include "ui_autorization.h"
#include "registration.h"
#include <QDebug>
#include <QMessageBox>

autorization::autorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::autorization)
{
    ui->setupUi(this);
    setMinimumSize(400, 300);
    setMaximumSize(400, 300);

    client_ = std::make_shared<Client>();
    client_->connect("127.0.0.1", 10020);

    if (!client_->is_connected()) {
      std::cout << "No connection\n" << std::endl;
      throw;
    }
}

autorization::autorization(QWidget* parent, std::shared_ptr<Client> client):
    QMainWindow(parent), ui(new Ui::autorization), client_(client)
{
    ui->setupUi(this);
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