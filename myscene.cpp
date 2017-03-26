#include "myscene.h"

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent) {

  QRect ecran = QApplication::desktop()->availableGeometry();
  int h = ecran.height();
  int w = ecran.width();

  tailleX = w/2;
  tailleY = h/2;

  posBallX = w/4;
  posBallY = h/4;

  sensX = 1;
  sensY = 1;

  scoreJ1 = 0;
  scoreJ2 = 0;

  //On gere le rectangle d'espace de jeu
  this->setSceneRect(0, 0, tailleX, tailleY);

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
  texte  = new QGraphicsTextItem("");
  texte->setPos(w/4 - 17, 2);
  texte->setScale(1);
  this->addItem(texte);

  //On affiche notre balle
  ball = new QGraphicsPixmapItem(QPixmap("ballon-icone-6652-16.png"));
  ball->setPos(posBallX, posBallY);
  this->addItem(ball) ;


  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);

}

void MyScene::CheckBord() {
  //Gère la largeur pour les rebonds
  if(ball->x()+sensX > tailleX) {
    sensX = -VITESSEX;
    scoreJ1++;
  }
  if(ball->x()+sensX < 0) {
    sensX = VITESSEX;
    scoreJ2++;
  }

  //Gère la hauteur pour les rebonds
  if(ball->y()+sensY > tailleY) {
    sensY = -VITESSEY;
  }
  if(ball->y()+sensY < 0) {
    sensY = VITESSEY;
  }
  // if(ball->x() == barre_gauche->x()+170) {
  //   for(int i = barre_gauche->y(); i < barre_gauche->y()+bgy; i++) {
  //     if(i == pic->y()) sensX = VITESSEX;
  //   }
  // }
  //
  // if(barre_gauche->collidesWithItem(pic) && sensX<0) {
  //   sensX = VITESSEX;
  // }
  // if(barre_droite->collidesWithItem(pic) && sensX<1604) {
  //   sensX = -VITESSEX;
  // }
}

void MyScene::update() {
  CheckBord();

  ball->setX(ball->x()+sensX);
  ball->setY(ball->y()+sensY);

  texte->setPlainText(QString::number(scoreJ1)+"   "+QString::number(scoreJ2));
  this->addItem(this->texte);
}

// void MyScene::keyPressEvent(QKeyEvent *event) {
//   if(event->key() == Qt::Key_A) {
//     if(bgy == -490) return;
//     else {
//       bgy = bgy -20;
//       barre_gauche->setPos(0,bgy);
//     }
//   }
//
//   if(event->key() == Qt::Key_Q) {
//     if(bgy == 380) return;
//     else {
//       bgy = bgy +20;
//       barre_gauche->setPos(0,bgy);
//     }
//   }
//
//   if(event->key() == Qt::Key_P) {
//     if(bdy == -490) return;
//     else {
//       bdy = bdy -20;
//       barre_droite->setPos(0,bdy);
//     }
//   }
//
//   if(event->key() == Qt::Key_M) {
//     if(bdy == 380) return;
//     else {
//       bdy = bdy +20;
//       barre_droite->setPos(0,bdy);
//     }
//   }
//
//   if(event->key() == Qt::Key_Space) {
//     if(timer->isActive()) {
//       timer->stop();
//       text_pause->setVisible(true);
//     } else {
//         timer->start(10);
//         text_pause->setVisible(false);
//     }
//
//   }
// }
