#include "./Interface/mainwindow.h"
#include "Interface/autorisation.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Autorisation w;
  w.show();
  return a.exec();
}