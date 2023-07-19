#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>
#include <vector>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<Client>& client)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client_(client)
{
    ui->setupUi(this);

    bool other_friends_exist;
    bool other_msg_exist;

    QVBoxLayout* lay = new QVBoxLayout(this);
    std::vector<std::string> FriendName = client->GetFriend(max_friend_in_page_, other_friends_exist);
    for (int i = 0; i < FriendName.size(); ++i) {
        QPushButton* button = new QPushButton(QString::fromStdString(FriendName[i]));
        // TO DO: formating button with long name !!!
        lay->insertWidget(count_friend_in_window++, button);
    }
    if (other_friends_exist) {
        QPushButton* button = new QPushButton("Другие друзья");
        lay->insertWidget(count_friend_in_window++, button);
    }
    ui->friendScrollAreaContext->setLayout(lay);

    // добавление истории чата на экран
    QVBoxLayout* mess = new QVBoxLayout(this);
    std::vector<std::string> message = client->GetMessage(max_count_line, other_msg_exist);
    for (int i = 0; i < message.size(); ++i) {
        QLabel* button2 = new QLabel(QString::fromStdString(message[i]));
        button2->setWordWrap(true);
        /*if (i % 3 == 0) {
            mess->addWidget(button2, count_msg_in_window++, 1);
            mess->addWidget(button2, count_msg_in_window, 0);
        } else {
            mess->addWidget(button2, count_msg_in_window++, 0);
            mess->addWidget(button2, count_msg_in_window, 1);
        }*/
        //button2->setStyleSheet("QLabel { background-color : #343B29; color : white; }");
        mess->insertWidget(count_msg_in_window++, button2);
    }
    ui->messageScrollAreaContext->setLayout(mess);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_friend_scroll_area_customContextMenuRequested(const QPoint &pos)
{
    if (pos.y() < 50) {
        QMessageBox::information(this, "Yes", "yes");
    }
}

std::string MainWindow::GetHTMLText(const std::string& str) {
    std::string html;
    html.resize(str.size() * 2);
    size_t pos = 0, h_pos = 0, next_pos, index_row = 0;
    for (; pos < str.size(); ) {
        next_pos = str.find(" ", pos);

        if (next_pos == std::string::npos) {
            for (; pos < str.size(); pos++, h_pos++) {
                html[h_pos] = str[pos];
            }
        } else {
            if (next_pos - pos < max_symbol_in_row - index_row) {
                for (; pos < next_pos + 1; pos++, h_pos++, index_row++) {
                    html[h_pos] = str[pos];
                }
            } else {
                html[h_pos++] = '<';
                html[h_pos++] = 'b';
                html[h_pos++] = 'r';
                html[h_pos++] = '>';
                index_row = 0;
                while (next_pos - pos >= max_symbol_in_row) {
                  for (int i = 0; i < max_symbol_in_row; i++, h_pos++, pos++) {
                    html[h_pos] = str[pos];
                  }
                  html[h_pos++] = '<';
                  html[h_pos++] = 'b';
                  html[h_pos++] = 'r';
                  html[h_pos++] = '>';
                }
                if (next_pos - pos < max_symbol_in_row) {
                  for (; pos < next_pos + 1; pos++, h_pos++, index_row++) {
                    html[h_pos] = str[pos];
                  }
                }
            }
        }
    }
    return html;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
   QMainWindow::resizeEvent(event);

   size_t width = this->size().width();
   size_t height = this->size().height();
}
