#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtWidgets>
#include <QBrush>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QKeyEvent>
#include <QObject>
#include <QRect>
#include <QPen>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QColor>
#include <QSound>
#include <cmath>

#define LARGEUR_RAQUETTE 1
#define LONGEUR_RAQUETTE 4

class MyScene : public QGraphicsScene {
  Q_OBJECT

  public:
    MyScene (QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void CheckBord();
    void pleinecran_myscene();
    void raquette_ia();
    void setIA(int ia);
    void setMap(int niveau);

  public slots:
    void update();

    void slot_reset();
    void slot_couleur();

    void slot_play();
    void slot_stop();

  private:
    QBrush brush;
    QColor couleur;

    QGraphicsRectItem *terrain;

    QGraphicsTextItem * pause;
    QGraphicsLineItem * ligneMid;
    QPixmap image_ball;
    QGraphicsPixmapItem * ball;
    QGraphicsRectItem *barre_gauche_item;
    QGraphicsRectItem *barre_droite_item;
    QGraphicsTextItem *texte;
    QTimer *timer;

    QSound *succes_coup;
    QSound *musique;

    QGraphicsRectItem *obstacle_1;
    QGraphicsRectItem *obstacle_2;

    int hauteur;
    int largeur;

    int posBallX;
    int posBallY;

    int tailleX;
    int tailleY;

    int sensX;
    int sensY;

    int scoreJ1;
    int scoreJ2;

    int hauteurD;
    int hauteurG;

    int vitesseX;
    int vitesseY;

    int largeur_raquette;
    int longeur_raquette;

    bool plein_ecran = false;

    int niveau_ia = 3;
    int niveau_map;
};

#endif
