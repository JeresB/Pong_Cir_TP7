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
#include <QButtonGroup>
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
    void slot_map();
    void slot_quit();

  private:
    QWidget *widget_general;

    QMenu *menuFichier;

    QGraphicsView *myview;
    MyScene *myscene;

    QAction *action_reset;
    QAction *action_couleur;

    QGroupBox *group_box;
    QVBoxLayout *box_control;
    QHBoxLayout *musique_controle;

    QPushButton *plein_ecran;
    QPushButton *reset;
    QPushButton *quitter;

    QLabel *niveau_ia;
    QButtonGroup *groupe_ia;
    QRadioButton *ia_1;
    QRadioButton *ia_2;
    QRadioButton *ia_3;

    QLabel *niveau_map;
    QButtonGroup *groupe_map;
    QRadioButton *map_1;
    QRadioButton *map_2;
    QRadioButton *map_3;
    QRadioButton *map_4;

    QLabel *musique;
    QPushButton *play;
    QPushButton *stop;

};

#endif
