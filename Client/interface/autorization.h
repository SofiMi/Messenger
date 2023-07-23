#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QMainWindow>
#include "mainwindow.h"
#include "../Client.h"
#include "../../include.h"

namespace Ui {
class autorization;
}

class autorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit autorization(QWidget *parent = nullptr);
    explicit autorization(QWidget *parent, std::shared_ptr<Client> client);
    ~autorization();

private slots:
    void on_to_main_clicked();

    void on_to_registration_clicked();

private:
    Ui::autorization *ui;
    MainWindow* main_window;
    std::shared_ptr<Client> client_;
};

#endif // AUTORIZATION_H
