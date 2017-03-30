#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  srand(time(NULL));
  QApplication appli(argc, argv);
  MainWindow window;

  window.show();

  return appli.exec();
}
