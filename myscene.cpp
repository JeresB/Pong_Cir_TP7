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

  largeur_raquette = LARGEUR_RAQUETTE * 0.02 * tailleX;
  longeur_raquette = LONGEUR_RAQUETTE * 0.04 * tailleY;

  //On gere le rectangle d'espace de jeu
  terrain = new QGraphicsRectItem(0, 0, tailleX, tailleY);
  terrain->setBrush(QColor(15, 72, 242));
  this->addItem(terrain);

  //On gère la barre qui bouge de gauche
  barre_gauche_item = new QGraphicsRectItem(tailleX * 0.05, tailleY * 0.5, largeur_raquette, longeur_raquette);
  barre_gauche_item->setBrush(QColor(0,255,0));
  this->addItem(barre_gauche_item) ;

  //On gère la barre qui bouge de droite
  barre_droite_item = new QGraphicsRectItem(tailleX * 0.95, tailleY * 0.5, largeur_raquette, longeur_raquette);
  barre_droite_item->setBrush(QColor(255,0,0));
  this->addItem(barre_droite_item) ;

  //ligne mediane
  QPen pen = QPen(Qt::white);
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
  try {
    image_ball = QPixmap("ball2.png");
    ball = new QGraphicsPixmapItem(image_ball);
    ball->setPos(posBallX, posBallY);
    this->addItem(ball);
    qDebug() << "[SUCCES] : Initialisation de la balle";
  } catch (...) {
    qWarning() << "[WARNING] : Problème de format de la balle";
  }


  obstacle_1 = new QGraphicsRectItem(450, 50, 5, 50);
  obstacle_1->setBrush(QColor(0,0,0));
  obstacle_2 = new QGraphicsRectItem(300, 200, 5, 50);
  obstacle_2->setBrush(QColor(0,0,0));


  //On gere le timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(30);
}

void MyScene::CheckBord() {
  //Gère la largeur pour les rebonds
  if(ball->x()+sensX+image_ball.width() > tailleX) {
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
  if(ball->y()+sensY+image_ball.height() > tailleY) {
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

  if (niveau_map == 2) {
    if(obstacle_1->collidesWithItem(ball) || obstacle_2->collidesWithItem(ball)) {
      sensX *= -1;
    }
  }
}

void MyScene::update() {
  CheckBord();

  ball->setX(ball->x()+sensX);
  ball->setY(ball->y()+sensY);
  raquette_ia();

  texte->setPlainText(QString::number(scoreJ1)+"          "+QString::number(scoreJ2));
  //this->addItem(this->texte);
}

void MyScene::raquette_ia() {
  if (sensY < niveau_ia) {
    hauteurD = ball->y() - longeur_raquette * 3.8;
    if(hauteurD >= tailleY * 0.32) return;
    if(hauteurD <= -longeur_raquette * 3) return;
    barre_droite_item->setPos(0, hauteurD);
  } else {
    if (sensY > 0) {
      hauteurD += niveau_ia;
      if(hauteurD <= -longeur_raquette * 3) return;
      else barre_droite_item->setPos(0, hauteurD);
    } else {
      if(hauteurD >= tailleY * 0.32) return;
      else {
        hauteurD -= niveau_ia;
        barre_droite_item->setPos(0, hauteurD);
      }
    }

  }
}

void MyScene::setIA(int ia) {
  niveau_ia = ia;
}

void MyScene::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_A) {
    if(hauteurG <= -longeur_raquette * 3) return;
    else {
      hauteurG = hauteurG -20;
      barre_gauche_item->setPos(0,hauteurG);
    }
  }
  if(event->key() == Qt::Key_Q) {
    if(hauteurG >= tailleY * 0.32) return;
    else {
      hauteurG = hauteurG +20;
      barre_gauche_item->setPos(0,hauteurG);
    }
  }

  if(event->key() == Qt::Key_P) {
    if(hauteurD <= -longeur_raquette * 3) return;
    else {
      hauteurD = hauteurD -20;
      barre_droite_item->setPos(0,hauteurD);
    }
  }

  if(event->key() == Qt::Key_M) {
    if(hauteurD >= tailleY * 0.32) return;
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
    largeur_raquette = LARGEUR_RAQUETTE * 0.02 * tailleX;
    longeur_raquette = LONGEUR_RAQUETTE * 0.04 * tailleY;
    terrain->setRect(0, 0, tailleX, tailleY);
    barre_gauche_item->setRect(tailleX * 0.05, tailleY * 0.5, largeur_raquette, longeur_raquette);
    barre_droite_item->setRect(tailleX * 0.95, tailleY * 0.5, largeur_raquette, longeur_raquette);
    ligneMid->setLine(0, 0, 0, tailleY);
    ligneMid->setPos(tailleX * 0.5, 0);
    texte->setPos(tailleX * 0.45, 2);
    texte->setScale(3);

  } else {
    plein_ecran = false;

    tailleX = largeur * 0.5;
    tailleY = hauteur * 0.5;
    largeur_raquette = LARGEUR_RAQUETTE * 0.02 * tailleX;
    longeur_raquette = LONGEUR_RAQUETTE * 0.04 * tailleY;
    terrain->setRect(0, 0, tailleX, tailleY);
    barre_gauche_item->setRect(tailleX * 0.05, tailleY * 0.5, largeur_raquette, longeur_raquette);
    barre_droite_item->setRect(tailleX * 0.95, tailleY * 0.5, largeur_raquette, longeur_raquette);
    ligneMid->setLine(0, 0, 0, tailleY);
    ligneMid->setPos(tailleX * 0.5, 0);
    texte->setPos(tailleX * 0.45, 2);
    texte->setScale(1);
  }
}

void MyScene::setMap(int niveau) {
  niveau_map = niveau;

  if (niveau == 1) {
    this->removeItem(obstacle_1);
    this->removeItem(obstacle_2);

  } else if (niveau == 2) {
    this->addItem(obstacle_1);
    this->addItem(obstacle_2);
    // if(obstacle_1->collidesWithItem(ball) || obstacle_2->collidesWithItem(ball)) {
    //   sensX *= -1;
    // }
  } else if (niveau == 3) {
    qDebug() << "En cours de programmation" << endl;
    this->removeItem(obstacle_1);
    this->removeItem(obstacle_2);
  } else {
    this->removeItem(obstacle_1);
    this->removeItem(obstacle_2);
  }
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
