#ifndef AUTORISATION_H
#define AUTORISATION_H

#include <QWidget>
#include "mainwindow.h"
#include "../Client.h"
#include "../../include.h"

namespace Ui {
class Autorisation;
}

class Autorisation : public QWidget
{
    Q_OBJECT

public:
    explicit Autorisation(QWidget *parent = nullptr);
    ~Autorisation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Autorisation *ui;
    MainWindow* main_window;
    std::shared_ptr<Client> client_;
};

#endif // AUTORISATION_H
