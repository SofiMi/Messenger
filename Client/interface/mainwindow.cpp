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

void MainWindow::timerEvent(QTimerEvent* event) {
  /* Обновление событий на экране,
     связанные с серверной частью.
     Происходит каждую секунду
     (startTimer в конструкторе).
  */
  // запрос новых сообщений в данном чате
  // client_->CheckUpdateByIdChat(chat_id_);

  // запрос старых сообщений / других друзей
  auto scrollBarMess = ui->messageScrollArea->verticalScrollBar();
  auto scrollBarFr = ui->friendScrollArea->verticalScrollBar();

  if (static_cast<double>(scrollBarMess->value()) /
          static_cast<double>(scrollBarMess->maximum()) <
      0.2) {
    AddOldMessages();
  }

  if (static_cast<double>(scrollBarFr->value()) /
          static_cast<double>(scrollBarFr->maximum()) >
      0.8) {
    AddOtherFriends();
  }

  // обработка новых сигналов от сервера
  if (client_->is_connected() && !client_->get_in_comming().empty()) {
    auto message = client_->get_in_comming().pop_front().msg;

    switch (message.header.id) {
    case msg_type::NewMessageToThisChat: {
      QString qstr = message.data.data();
      AddNewMessage(qstr);
      break;
    }
    case msg_type::NewMessageToOtherChat: {
      break;
    }
    }
  }
}

void MainWindow::AddOldMessages() {
  /* Добавление в messageScrollArea старых сообщений. */
  std::vector<std::string> messages = client_->GetMessage(15);
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());

  for (int i = messages.size() - 1; i > -1; --i) {
    QLabel* message = new QLabel(QString::fromStdString(messages[i]));
    message->setWordWrap(true);
    messages_box_layout->insertWidget(0, message);
  }
}

void MainWindow::AddNewMessage(const QString& qstr) {
  /* Добавление в messageScrollArea новое сообщение. */
  QVBoxLayout* messages_box_layout =
      dynamic_cast<QVBoxLayout *>(ui->messageScrollAreaContext->layout());
  QLabel* message = new QLabel(qstr);
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
    QObject::connect(button, &QPushButton::clicked,
     [this]() {
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

