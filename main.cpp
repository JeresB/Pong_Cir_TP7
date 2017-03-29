#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  QApplication appli(argc, argv);
  MainWindow window;

  window.show();

  return appli.exec();
}
