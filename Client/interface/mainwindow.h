#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, std::shared_ptr<Client>& client);
    ~MainWindow();

private slots:
    void on_SendMsg_clicked(bool checked);

private:
  void resizeEvent(QResizeEvent* event);

  void AddOldMessages();
  void AddNewMessage(const QString& qstr);
  void AddOtherFriends();

  Ui::MainWindow* ui;
  int timerId; // to timerEvent

  std::shared_ptr<Client> client_;
  size_t chat_id_ = 0;
};
#endif // MAINWINDOW_H
