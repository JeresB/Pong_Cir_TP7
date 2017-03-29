#include "myscene.h"

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent) {

  QRect ecran = QApplication::desktop()->availableGeometry();
  int h = ecran.height();
  int w = ecran.width();

  if (plein_ecran == 1) {
    tailleX = w;
    tailleY = h;
  } else {
    tailleX = w/2;
    tailleY = h/2;
  }

  posBallX = w/4;
  posBallY = h/4;

  sensX = 1;
  sensY = 1;

  scoreJ1 = 0;
  scoreJ2 = 0;

  hauteurG = 50;
  hauteurD = 50;

  vitesseX = 2;
  vitesseY = 1;

  //On gere le rectangle d'espace de jeu
  this->setSceneRect(0, 0, tailleX, tailleY);
  this->setBackgroundBrush(Qt::blue);

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

  // On gère l'affichage du text de pause
  pause  = new QGraphicsTextItem( "PAUSE - Espace pour continuer !");
  pause->setPos(tailleX/5, tailleY/3);
  pause->setScale(2);
  this->addItem(this->pause);
  pause->setVisible(false);

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
    vitesseX = 2;
    vitesseY = 1;
    sensX = -vitesseX;
    scoreJ1++;
  }
  if(ball->x()+sensX < 0) {
    vitesseX = 2;
    vitesseY = 1;
    sensX = vitesseX;
    scoreJ2++;
  }

  //Gère la hauteur pour les rebonds
  if(ball->y()+sensY > tailleY) {
    sensY = -vitesseY;
  }
  if(ball->y()+sensY < 0) {
    sensY = vitesseY;
  }

  // Collision avec la barre de gauche
  if(barre_gauche_item->collidesWithItem(ball) && sensX<0) {
    sensX = vitesseX;
    vitesseX++;
  }
  // Collision avec la barre de droite
  if(barre_droite_item->collidesWithItem(ball) && sensX<tailleX) {
    sensX = -vitesseX;
    vitesseX++;
    vitesseY++;
  }
}

void MyScene::update() {
  CheckBord();

  ball->setX(ball->x()+sensX);
  ball->setY(ball->y()+sensY);

  texte->setPlainText(QString::number(scoreJ1)+"   "+QString::number(scoreJ2));
  //this->addItem(this->texte);
}

void MyScene::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_A) {
    if(hauteurG <= -50) return;
    else {
      hauteurG = hauteurG -20;
      barre_gauche_item->setPos(0,hauteurG);
    }
  }
  if(event->key() == Qt::Key_Q) {
    if(hauteurG >= tailleY - 100) return;
    else {
      hauteurG = hauteurG +20;
      barre_gauche_item->setPos(0,hauteurG);
    }
  }

  if(event->key() == Qt::Key_P) {
    if(hauteurD <= -50) return;
    else {
      hauteurD = hauteurD -20;
      barre_droite_item->setPos(0,hauteurD);
    }
  }

  if(event->key() == Qt::Key_M) {
    if(hauteurD >= tailleY - 100) return;
    else {
      hauteurD = hauteurD +20;
      barre_droite_item->setPos(0,hauteurD);
    }
  }

  if(event->key() == Qt::Key_Space) {
    if(timer->isActive()) {
      timer->stop();
      pause->setVisible(true);
    } else {
        timer->start(30);
        pause->setVisible(false);
    }
  }
}

void MyScene::slot_pleinecran() {
  if (plein_ecran == 0) {
    plein_ecran = 1;
    this->setSceneRect(0, 0, 1300, 700);


  } else {
    plein_ecran = 0;
    this->setSceneRect(0, 0, tailleX, tailleY);
  }

}

int MyScene::getPleinEcran() {
  return plein_ecran;
}
