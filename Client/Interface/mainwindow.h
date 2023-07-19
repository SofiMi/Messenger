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
    void on_friend_scroll_area_customContextMenuRequested(const QPoint &pos);

private:
    void resizeEvent(QResizeEvent*);
    Ui::MainWindow* ui;
    std::shared_ptr<Client> client_;

    const int max_friend_in_page_ = 14;
    const int max_count_line = 20;

    int count_friend_in_window = 0;
    int count_msg_in_window = 0;

    std::string GetHTMLText(const std::string& str);
    size_t max_symbol_in_row = 50;
};
#endif // MAINWINDOW_H
