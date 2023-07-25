#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollBar>
#include <QTimer>
#include <QVBoxLayout>
#include <string>
#include <vector>

static int i = 0;

void updateCompass() { std::cout << (i++) << std::endl; }

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<Client> &client)
    : QMainWindow(parent), ui(new Ui::MainWindow), client_(client) {
  ui->setupUi(this);

  QVBoxLayout *lay = new QVBoxLayout(this);
  ui->friendScrollAreaContext->setLayout(lay);
  AddOtherFriends();

  QVBoxLayout *messages_box_layout = new QVBoxLayout(this);
  ui->messageScrollAreaContext->setLayout(messages_box_layout);

  timerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  /* Обновление размера экрана */
  QMainWindow::resizeEvent(event);
  size_t width = this->size().width();
  size_t height = this->size().height();
}

void MainWindow::AddOldMessages() {
  /* Добавление в messageScrollArea старых сообщений. */
  std::vector<std::string> messages = client_->GetMessage();
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

  for (int i = messages.size() - 1; i > -1; --i) {
    QLabel* message = new QLabel(QString::fromStdString(messages[i]));
    message->setStyleSheet("QLabel { background-color : white }");
    message->setWordWrap(true);
    messages_box_layout->insertWidget(0, message);
  }
}

void MainWindow::AddNewMessage(const QString& qstr) {
  /* Добавление в messageScrollArea новое сообщение. */
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());
  QLabel* message = new QLabel(qstr);
  message->setStyleSheet("background-color: yellow");
  message->setWordWrap(true);
  messages_box_layout->addWidget(message);
}

void MainWindow::AddOtherFriends() {
  /* Добавление в friendScrollArea других друзей. */
  auto friend_name = client_->GetChats();
  QVBoxLayout* friend_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->friendScrollAreaContext->layout());

  for (int i = 0; i < friend_name.size(); ++i) {
    QPushButton* button = new QPushButton(QString::fromStdString(friend_name[i].second));
    chatid_map[friend_name[i].first] = button;
    QObject::connect(button, &QPushButton::clicked,
     [this, chatid = friend_name[i].first]() {
      client_->chatid_ = chatid;
      client_->GetLastIdMessage();
      //std::cout << "chatid " << client_->chatid_ << " last_accept_message_id_in_chat_ " << client_->last_accept_message_id_in_chat_ << std::endl;
      while (auto* item = ui->messageScrollAreaContext->layout()->takeAt(0)) {
        delete item->widget();
        delete item;
      }
      AddOldMessages();
    });
    // TO DO: formating button with long name !!!
    friend_box_layout->addWidget(button);
  }
}


void MainWindow::on_SendMsg_clicked(bool checked) {
  std::cout << "\n[on_SendMsg_clicked]" << std::endl;
  /* Отправление нового сообщения */
  QString qtext = ui->InputMsg->text();

  if (qtext.toStdString().size() > 0) {
     ui->InputMsg->clear();

    // Добавляем сообщение в чат
    QVBoxLayout* messages_box_layout =
        dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());
    
    QLabel* new_message = new QLabel(qtext);
    new_message->setStyleSheet("QLabel { background-color : white }");
    new_message->setWordWrap(true);
    messages_box_layout->addWidget(new_message);

    // Передача сообщения серверу
    std::string text = qtext.toStdString();
    client_->SendNewMessage(text);
  } else {
    QMessageBox::about(this, "Неправильный ввод", "Сообщение не может быть пустым.");
  }
  std::cout << "[on_SendMsg_clicked]\n" << std::endl;
}

void MainWindow::timerEvent(QTimerEvent* event) {
  //std::cout << "Timer" << std::endl;
  //std::vector<std::string> res = client_->GetDataUpdate();
  //for (int i = 0; i < res.size(); ++i) {
    //std::cout << res[i] << " " << std::endl;
  //}
}

void MainWindow::on_findNick_clicked() {
  int chatid;
  std::string namechat = "Chat";
  std::string nick = ui->inputNick->text().toStdString();

    if (nick[0] == '@') {
      if (client_->CheckUniqueNickname(nick)) {
        QMessageBox::about(this, "Неудачный поиск", "Такого пользователя не существует.");
        return;
      } else {
        if (client_->CheckTetAtTetChat(nick, chatid, namechat)) {
          if (chatid_map.find(chatid) != chatid_map.end()) {
            delete chatid_map[chatid];
          }
        } else {
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "", "Начать новый диалог",
                                QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
            chatid = client_->CreateNewChat(nick, namechat);
          } else {
            return;
          }
        }
      }
    }

    if (nick[0] != '@') {
      if (!client_->CheckChatName(nick, chatid)) {
        QMessageBox::about(this, "Неудачный поиск", "Чата с таким именем не существует. Попробуйте искать через глобальный поиск(@...)");
        return;
      } else {
        delete chatid_map[chatid];
      }
    }

    QVBoxLayout* friend_box_layout =
        dynamic_cast<QVBoxLayout *>(ui->friendScrollAreaContext->layout());

    QPushButton* button = new QPushButton(QString::fromStdString(namechat));
    QObject::connect(button, &QPushButton::clicked,
     [this, chatid]() {
      client_->chatid_ = chatid;
      client_->GetLastIdMessage();
      while (auto* item = ui->messageScrollAreaContext->layout()->takeAt(0)) {
        delete item->widget();
        delete item;
      }
      AddOldMessages();
    });
    // TO DO: formating button with long name !!!
    friend_box_layout->insertWidget(0, button);
}

