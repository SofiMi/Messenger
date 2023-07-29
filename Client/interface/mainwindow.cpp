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

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<Client> &client)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      client_(client) {
  ui->setupUi(this);

  // область с чатами
  QVBoxLayout* friend_box_layout = new QVBoxLayout(this);
  ui->friendScrollAreaContext->setLayout(friend_box_layout);
  AddOtherFriends();

  // область с сообщениями
  QVBoxLayout* messages_box_layout = new QVBoxLayout(this);
  ui->messageScrollAreaContext->setLayout(messages_box_layout);

  // устанавливаем обновление каждую секунду
  timerId = startTimer(1000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::AddOldMessages(bool maximum_scrollbar) {
  /* Добавление в messageScrollArea старых сообщений. */
  std::vector<std::string> messages = client_->GetMessage();
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

  QLabel* message;
  for (int i = messages.size() - 1; i > -1; --i) {
    //widget = new QWidget();
    message = new QLabel(QString::fromStdString(messages[i]));
    message->setStyleSheet("QLabel { background-color : white }");
    message->setWordWrap(true);
    if (maximum_scrollbar) {
      QPushButton* butt = new QPushButton(message);
      connect(butt, &QPushButton::released, this, &MainWindow::handleButton);
      butt->hide();

      messages_box_layout->insertWidget(0, message);
      butt->animateClick();
      ui->messageScrollArea->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
    }
    messages_box_layout->insertWidget(0, message);
  }
}

void MainWindow::AddNewMessage(const QString& qstr) {
  /* Добавление в messageScrollArea новое сообщение. */
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

  QWidget* widget = new QWidget();
  QLabel* message = new QLabel(qstr);
  message->setStyleSheet("background-color: yellow");
  message->setWordWrap(true);

  QPushButton* butt = new QPushButton(message);
  connect(butt, &QPushButton::released, this, &MainWindow::handleButton);
  messages_box_layout->addWidget(message);
  butt->animateClick();
  ui->messageScrollArea->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
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
      while (auto* item = ui->messageScrollAreaContext->layout()->takeAt(0)) {
        delete item->widget();
        delete item;
      }
      AddOldMessages(true);
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

    // Передача сообщения серверу
    std::string text = qtext.toStdString();
    client_->SendNewMessage(text);

    std::vector<std::string> res = client_->GetDataUpdate();

    QVBoxLayout* messages_box_layout =
          dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

    for (int i = 0; i < res.size(); ++i) {
      std::cout << res[i] << " " << std::endl;
      QLabel* new_message = new QLabel(res[i].c_str());
      new_message->setStyleSheet("QLabel { background-color : white }");
      new_message->setWordWrap(true);

      QPushButton* butt = new QPushButton(new_message);
      connect(butt, &QPushButton::released, this, &MainWindow::handleButton);
      messages_box_layout->addWidget(new_message);
      butt->animateClick();
      butt->hide();
      ui->messageScrollArea->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
    }
  } else {
    QMessageBox::about(this, "Неправильный ввод", "Сообщение не может быть пустым.");
  }
  std::cout << "[on_SendMsg_clicked]\n" << std::endl;
}

void MainWindow::timerEvent(QTimerEvent* event) {
  //std::cout << "Timer" << std::endl;

  auto scrollBarMess = ui->messageScrollArea->verticalScrollBar();
  auto scrollBarFr = ui->friendScrollArea->verticalScrollBar();

  if (static_cast<double>(scrollBarMess->value()) / static_cast<double>(scrollBarMess->maximum()) < 0.2) {
    AddOldMessages();
  }

  if (static_cast<double>(scrollBarMess->value()) / static_cast<double>(scrollBarMess->maximum()) < 0.2) {
    AddOtherFriends();
  }

  std::vector<std::string> res = client_->GetDataUpdate();

  QVBoxLayout* messages_box_layout =
        dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

  QWidget* widget = new QWidget();
  for (int i = 0; i < res.size(); ++i) {
    QLabel* new_message = new QLabel(res[i].c_str(), widget);
    new_message->setStyleSheet("QLabel { background-color : white }");
    new_message->setWordWrap(true);
    if (i != res.size() - 1)
      messages_box_layout->addWidget(widget);
  }

  if (res.size() > 0) {
    QPushButton* butt = new QPushButton(widget);
    connect(butt, &QPushButton::released, this, &MainWindow::handleButton);
    messages_box_layout->addWidget(widget);
    butt->animateClick();
    ui->messageScrollArea->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
  }
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

void MainWindow::scrollToBottom(int min, int max) {
  (void) min;
  if (max > scrollBarMax) ui->messageScrollArea->verticalScrollBar()->setValue(max);
  scrollBarMax = max;
}

void MainWindow::handleButton() {
  ui->messageScrollArea->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
}

