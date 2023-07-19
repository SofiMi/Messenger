#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>
#include <vector>
#include <string>
#include <QMessageBox>

class Client {
 static int count_;
 public:
    std::vector<std::string> GetFriend(int count, bool& is_other_friend_exists) {
        is_other_friend_exists = true;
        std::vector<std::string> res = {{"Sofia"}, {"Alex"}};
        /*std::string str = "София";
        for (int i = 0; i < count; i++) {
            str += i + '0';
            res.push_back(str);
        }*/
        return res;
   }

    std::vector<std::string> GetMessage(int count, bool& other_messages_exists) {
        std::vector<std::string> res = {
            {"123456789"},
            {"Всем привет. Через две недели выступаю вот здесь: https://cppzerocostconf.yandex.ru/cxxzerocostconf_2023 "
             "с докладом про векторизацию. Сначала разберём всю боль обычной векторизации, повекторизуем руками некоторые вещи."
             " Потом я представлю масштабируемую векторизацию, это новая концепция которая сейчас набирает обороты в ARM и RISCV. "
             "Посмотрим как она решает проблемы. А потом поговорим о том как она создаёт проблемы"
             "Можно рассматривать это как продолжение записанного мной "
             "прошлым летом допсеминара про SIMD, см. https://t.me/cpp_lects_rus/27"
             "Вход на площадку свободный, но по регистрации. Которую можно пройти уже сейчас."
             "Меня пока в программе нет, но я появлюсь, доклад согласовали."},
            {"Да. Я вас понял. Все будет сделано в лучшем порядке."}
        };
        return res;
   }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // окно фиксированного размера
    //setMinimumSize(750, 600);
    //setMaximumSize(750, 600);

    bool other_friends_exist;
    bool other_msg_exist;

    // добавление друзей на экран
    QVBoxLayout* lay = new QVBoxLayout(this);
    std::vector<std::string> FriendName = client->GetFriend(max_friend_in_page_, other_friends_exist);
    for (int i = 0; i < FriendName.size(); ++i) {
        QPushButton* button = new QPushButton(QString::fromStdString(FriendName[i]));
        lay->insertWidget(count_friend_in_window++, button);
    }
    if (other_friends_exist) {
        QPushButton* button = new QPushButton("Другие друзья");
        lay->insertWidget(count_friend_in_window++, button);
    }
    ui->friend_scroll_area_context->setLayout(lay);

    // добавление истории чата на экран
    QVBoxLayout* mess = new QVBoxLayout(this);
    std::vector<std::string> message = client->GetMessage(max_count_line, other_msg_exist);
    for (int i = 0; i < message.size(); ++i) {
        QLabel* button2 = new QLabel(QString::fromStdString(GetHTMLText(message[i]).c_str()));
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
    ui->message_scroll_area_context->setLayout(mess);

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
