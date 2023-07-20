#ifndef AUTORISATION_H
#define AUTORISATION_H

#include <QWidget>
#include "mainwindow.h"
#include "../Client.h"
#include "../../include.h"

namespace Ui {
class autorisation;
}

class autorisation : public QWidget
{
    Q_OBJECT

public:
    explicit autorisation(QWidget *parent = nullptr);
    ~autorisation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::autorisation *ui;
    MainWindow* main_window;
    std::shared_ptr<Client> client_;
};

#endif // AUTORISATION_H
