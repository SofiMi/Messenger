#include "autorisation.h"
#include "ui_autorisation.h"

Autorisation::Autorisation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Autorisation)
{
    ui->setupUi(this);
    // окно фиксированного размера
    setMinimumSize(400, 300);
    setMaximumSize(400, 300);
}

Autorisation::~Autorisation()
{
    delete ui;
}

void Autorisation::on_pushButton_clicked() {
   QString login = ui->login->text();
   QString password = ui->password->text();
   if (login == "" && password == "") {
       hide();
       main_window = new MainWindow(this);
       main_window->show();
   }
}

