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
//#include <QSlider>
#include <QMenuBar>
#include <QRadioButton>
#include <QLabel>
#include "myscene.h"

#define IA_NIVEAU_1 3
#define IA_NIVEAU_2 6
#define IA_NIVEAU_3 10

class MainWindow : public QMainWindow {
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGroupBox *BuildGroupBoxControle();

  public slots:
    void slot_pleinecran();
    void slot_ia();

  private:
    QWidget *widget_general;
    QMenu *menuFichier;
    QGraphicsView *myview;
    MyScene *myscene;
    QAction *action_reset;
    QAction *action_couleur;
    QGroupBox *group_box;
    QPushButton *plein_ecran;
    QPushButton *quitter;
    QVBoxLayout *box_control;
    QRadioButton *ia_1;
    QRadioButton *ia_2;
    QRadioButton *ia_3;
    QLabel *niveau_ia;
};

#endif
