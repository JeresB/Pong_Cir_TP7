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
#include <QScrollBar>
#include <QSlider>
#include <QMenuBar>
#include "myscene.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGroupBox *BuildGroupBoxControle();
    int getPleinEcran();

  public slots:
    void slot_pleinecran();

  private:
    QWidget *widget_general;
    QMenu *menuFichier;
    QGraphicsView *myview;
    MyScene *myscene;
    QAction *action_reset;
    QAction *action_couleur;
};

#endif
