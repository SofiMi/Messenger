#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include "../Client.h"

namespace Ui {
class Registration;
}

class Registration : public QMainWindow {
    Q_OBJECT

 public:
    explicit Registration(QWidget* parent, std::shared_ptr<Client>& client);
    ~Registration();

private slots:
    void on_to_autorization_clicked();
    void on_registration_clicked();

private:
    Ui::Registration* ui;
    std::shared_ptr<Client> client_;
    void add_style();
};

#endif // REGISTRATION_H
