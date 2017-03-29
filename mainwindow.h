#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QGroupBox>
#include <QAction>
#include <QPushButton>
#include "myscene.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGroupBox *BuildGroupBoxControle();
    int getPleinEcran();

  public slots:

  private:
    QWidget *widget_general;
    QMenu *menuFichier;
    QGraphicsView *myview;
    MyScene *myscene;
    QAction *action_couleur;
};

#endif
