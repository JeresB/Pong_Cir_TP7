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

class MyScene : public QGraphicsScene {
  Q_OBJECT

  public:
    MyScene (QObject *parent = 0);
    void mouvement();

  public slots:
    void update();

  private:
    QBrush brush;
    QColor couleur;

    QGraphicsTextItem * text_pause;
    QGraphicsLineItem * ligneMid;
    QGraphicsPixmapItem * ball;
    QGraphicsRectItem *barre_gauche_item;
    QGraphicsRectItem *barre_droite_item;
    QGraphicsTextItem *texte;
    QTimer *timer;

};

#endif
