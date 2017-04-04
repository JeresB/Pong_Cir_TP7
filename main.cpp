#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  srand(time(NULL)); // Réel Aléatoire
  qDebug() << "[SUCCES] : Initialisation srand : temps aléatoire";

  QApplication appli(argc, argv); // Application
  qDebug() << "[SUCCES] : Initialisation QApplication";
  // Création et affichage de la fenêtre principale
  MainWindow window;
  qDebug() << "[SUCCES] : Création de la fenêtre principale";
  window.show();
  qDebug() << "[SUCCES] : Affichage de la fenêtre principale";

  // Execution de l'application
  try {
    qDebug() << "[SUCCES] : Démarrage de l'application";
    return appli.exec();
  } catch (...) {
    qCritical() << "[ERREUR] : Echec de l'execution de l'application";
  }
}
