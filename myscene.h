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

class MyScene : public QGraphicsScene {
  Q_OBJECT

  public:
    MyScene (QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void CheckBord();
    int getPleinEcran();

  public slots:
    void update();
    //void slot_pleinecran();
    void slot_setVitesse(int);
    void slot_reset();
    void slot_couleur();

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

    int vitesseX;
    int vitesseY;

    int plein_ecran = 0;
};

#endif
