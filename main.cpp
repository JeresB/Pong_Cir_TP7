#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  srand(time(NULL)); // Réel Aléatoire
  QApplication appli(argc, argv); // Application

  // Création et affichage de la fenêtre principale
  MainWindow window;
  window.show();

  // Execution de l'application
  return appli.exec();
}
