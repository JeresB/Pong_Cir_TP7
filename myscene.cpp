#include "myscene.h"

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent) {

  QRect ecran = QApplication::desktop()->availableGeometry();
  hauteur = ecran.height();
  largeur = ecran.width();

  tailleX = largeur * 0.5;
  tailleY = hauteur * 0.5;

  posBallX = largeur * 0.25;
  posBallY = hauteur * 0.25;

  sensX = 1;
  sensY = 1;

  scoreJ1 = 0;
  scoreJ2 = 0;

  hauteurG = 50;
  hauteurD = 50;

  vitesseX = 2;
  vitesseY = 1;

  //On gere le rectangle d'espace de jeu
  terrain = new QGraphicsRectItem(0, 0, tailleX, tailleY);
  terrain->setBrush(Qt::blue);
  this->addItem(terrain);

  //On gère la barre qui bouge de gauche
  barre_gauche_item = new QGraphicsRectItem(tailleX * 0.1, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
  barre_gauche_item->setBrush(QColor(0,0,0));
  this->addItem(barre_gauche_item) ;

  //On gère la barre qui bouge de droite
  barre_droite_item = new QGraphicsRectItem(tailleX * 0.9, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
  barre_droite_item->setBrush(QColor(0,0,0));
  this->addItem(barre_droite_item) ;

  //ligne mediane
  QPen pen = QPen(Qt::red);
  pen.setWidth(3);
  pen.setStyle(Qt::DashLine);
  ligneMid = new QGraphicsLineItem(0, 0, 0, hauteur/2);
  ligneMid->setPos(largeur/4, 2);
  ligneMid->setPen(pen);
  this->addItem(ligneMid) ;

  //On gere l'affichage du score
  texte  = new QGraphicsTextItem("");
  texte->setPos(tailleX * 0.45, 2);
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

  texte->setPlainText(QString::number(scoreJ1)+"          "+QString::number(scoreJ2));
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

void MyScene::pleinecran_myscene() {
  qDebug() << "plein ecran myscene";
  if (plein_ecran == false) {
    plein_ecran = true;

    tailleX = largeur * 0.9;
    tailleY = hauteur * 0.9;
    terrain->setRect(0, 0, tailleX, tailleY);
    barre_gauche_item->setRect(tailleX * 0.1, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
    barre_droite_item->setRect(tailleX * 0.9, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
    ligneMid->setLine(0, 0, 0, tailleY);
    ligneMid->setPos(tailleX * 0.5, 0);
    texte->setPos(tailleX * 0.45, 2);
    texte->setScale(3);

  } else {
    plein_ecran = false;

    tailleX = largeur * 0.5;
    tailleY = hauteur * 0.5;
    terrain->setRect(0, 0, tailleX, tailleY);
    barre_gauche_item->setRect(tailleX * 0.1, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
    barre_droite_item->setRect(tailleX * 0.9, tailleY * 0.5, LARGEUR_RAQUETTE * 0.02 * tailleX, LONGEUR_RAQUETTE * 0.05 * tailleY);
    ligneMid->setLine(0, 0, 0, tailleY);
    ligneMid->setPos(tailleX * 0.5, 0);
    texte->setPos(tailleX * 0.45, 2);
    texte->setScale(1);
  }
}

void MyScene::slot_setVitesse(int nouveau) {
  sensX *= nouveau;
  sensY *= nouveau/2;
}

void MyScene::slot_reset() {
  scoreJ1 = 0;
  scoreJ2 = 0;
  texte->setPlainText(QString::number(scoreJ1)+"   "+QString::number(scoreJ2));
}

void MyScene::slot_couleur() {
  int R = rand()%255;
  int G = rand()%255;
  int B = rand()%255;

  this->setBackgroundBrush(QColor(R, G, B));
}
