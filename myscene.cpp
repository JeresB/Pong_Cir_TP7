#include "myscene.h"

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent) {

  QRect ecran = QApplication::desktop()->availableGeometry();
  int h = ecran.height();
  int w = ecran.width();
  //On gere le rectangle d'espace de jeu
  this->setSceneRect(0, 0, w /2, h /2);

  //On gère la barre qui bouge de gauche
  barre_gauche_item = new QGraphicsRectItem(50, 50, 10, 40);
  barre_gauche_item->setBrush(QColor(0,0,0));
  this->addItem(barre_gauche_item) ;

  //On gère la barre qui bouge de droite
  barre_droite_item = new QGraphicsRectItem(w/2 -50, 50, 10, 40);
  barre_droite_item->setBrush(QColor(0,0,0));
  this->addItem(barre_droite_item) ;

  //ligne mediane
  ligneMid = new QGraphicsLineItem(0, 0, 0, h/2);
  ligneMid->setPos(w/4, 2);
  ligneMid->setPen(QPen(Qt::red));
  this->addItem(ligneMid) ;

  //On gere l'affichage du score
  texte  = new QGraphicsTextItem("score");
  texte->setPos(w/4 - 20, 2);
  texte->setScale(1);
  this->addItem(texte);

  //On affiche notre balle
  ball = new QGraphicsPixmapItem(QPixmap("ballon-icone-6652-16.png"));
  ball->setPos(w/4, h/4);
  this->addItem(ball) ;


  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);

  }


void MyScene::update() {
  mouvement();
}

void MyScene::mouvement() {

}
