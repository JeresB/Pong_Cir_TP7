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

#define VITESSEX 2;
#define VITESSEY 1;

class MyScene : public QGraphicsScene {
  Q_OBJECT

  public:
    MyScene (QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void CheckBord();

  public slots:
    void update();

  private:
    QBrush brush;
    QColor couleur;

    QGraphicsTextItem * pause;
    QGraphicsLineItem * ligneMid;
    QGraphicsPixmapItem * ball;
    QGraphicsRectItem *barre_gauche_item;
    QGraphicsRectItem *barre_droite_item;
    QGraphicsTextItem *texte;
    QTimer *timer;

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

};

#endif
