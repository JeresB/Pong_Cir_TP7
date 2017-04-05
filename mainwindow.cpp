#include "mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Pong"); // Nom de la fenêtre
  qDebug() << "[SUCCES] : Initialisation du nom de la fenêtre : Pong";

  widget_general = new QWidget;
  qDebug() << "[SUCCES] : Création du widget général";
  QHBoxLayout *qbl_general = new QHBoxLayout;
  qDebug() << "[SUCCES] : Création du QHBoxLayout";

  // Création du widget principale
  widget_general->setLayout(qbl_general);
  qDebug() << "[SUCCES] : Initialisation du QHBoxLayout vers le widget général";
  this->setCentralWidget(widget_general);
  qDebug() << "[SUCCES] : Initialisation du widget général vers la fenêtre principale";

  // Création de la scène de jeu
  myscene = new MyScene(this);
  qDebug() << "[SUCCES] : Création de la scène de jeu";
  myscene->setBackgroundBrush(QColor(13, 139, 242));
  qDebug() << "[SUCCES] : Initialisation de la couleur de la scène de jeu";
  myview = new QGraphicsView(myscene, this);
  qDebug() << "[SUCCES] : Création de la vue graphique";

  qbl_general->addWidget(BuildGroupBoxControle());
  qDebug() << "[SUCCES] : Initialisation du widget de contôle vers le QHBoxLayout";
  qbl_general->addWidget(myview);
  qDebug() << "[SUCCES] : Initialisation de la vue graphique vers le  QHBoxLayout";

  // Action permettant de reset le score des joueurs
  action_reset = new QAction(tr("&Reset"), this);
  qDebug() << "[SUCCES] : Création de l'action reset";

  // Action permettant de changer la couleur du fond
  action_couleur = new QAction(tr("&Couleur"), this);
  qDebug() << "[SUCCES] : Création de l'action couleur";

  // Création du menu et ajout de nos actions
  menuFichier = menuBar()->addMenu(tr("&Fichier"));
  qDebug() << "[SUCCES] : Création du menu fichier";
  menuFichier->addAction(action_reset);
  qDebug() << "[SUCCES] : Initialisation de l'action reset";
  menuFichier->addAction(action_couleur);
  qDebug() << "[SUCCES] : Initialisation de l'action couleur";

  try {
    connect(action_couleur, SIGNAL(triggered()), myscene, SLOT(slot_couleur()));
  } catch (...) {
    qWarning() << "[WARNING] : Connexion du reset non effectué";
  }

  try {
    connect(action_reset, SIGNAL(triggered()), myscene, SLOT(slot_reset()));
  } catch (...) {
    qWarning() << "[WARNING] : Génération de la nouvelle couleur non effectué";
  }
}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  group_box = new QGroupBox(tr("Contrôle"));

  plein_ecran = new QPushButton("Plein Ecran", this);

  niveau_ia = new QLabel("Niveau de l'IA", this);
  groupe_ia = new QButtonGroup(this);
  ia_1 = new QRadioButton("Niveau 1", this);
  ia_1->setChecked(true);
  ia_2 = new QRadioButton("Niveau 2", this);
  ia_3 = new QRadioButton("Niveau 3", this);
  groupe_ia->addButton(ia_1);
  groupe_ia->addButton(ia_2);
  groupe_ia->addButton(ia_3);

  niveau_map = new QLabel("Niveau de la map", this);
  groupe_map = new QButtonGroup(this);
  map_1 = new QRadioButton("Simple", this);
  map_1->setChecked(true);
  map_2 = new QRadioButton("Obstacles", this);
  map_3 = new QRadioButton("Teleporter", this);
  map_4 = new QRadioButton("The Big Wall", this);
  groupe_map->addButton(map_1);
  groupe_map->addButton(map_2);
  groupe_map->addButton(map_3);
  groupe_map->addButton(map_4);

  musique = new QLabel("Musique", this);

  QPixmap play_img = QPixmap("play.png");
  QIcon play_icon = QIcon(play_img);
  play = new QPushButton(this);
  play->setIcon(play_icon);
  play->setIconSize(play_img.rect().size());

  QPixmap stop_img = QPixmap("stop.png");
  QIcon stop_icon = QIcon(stop_img);
  stop = new QPushButton(this);
  stop->setIcon(stop_icon);
  stop->setIconSize(stop_img.rect().size());


  quitter = new QPushButton("Quitter", this);

  box_control = new QVBoxLayout;
  musique_controle = new QHBoxLayout;
    musique_controle->addWidget(play);
    musique_controle->addWidget(stop);

    box_control->addWidget(plein_ecran);

    box_control->addWidget(niveau_ia);
    box_control->addWidget(ia_1);
    box_control->addWidget(ia_2);
    box_control->addWidget(ia_3);

    box_control->addWidget(niveau_map);
    box_control->addWidget(map_1);
    box_control->addWidget(map_2);
    box_control->addWidget(map_3);
    box_control->addWidget(map_4);

    box_control->addWidget(musique);
    box_control->addLayout(musique_controle);

    box_control->addWidget(quitter);

    box_control->addStretch(1);
    group_box->setLayout(box_control);

  connect(plein_ecran, SIGNAL(clicked()), this, SLOT(slot_pleinecran()));

  connect(ia_1, SIGNAL(clicked()), this, SLOT(slot_ia()));
  connect(ia_2, SIGNAL(clicked()), this, SLOT(slot_ia()));
  connect(ia_3, SIGNAL(clicked()), this, SLOT(slot_ia()));

  connect(map_1, SIGNAL(clicked()), this, SLOT(slot_map()));
  connect(map_2, SIGNAL(clicked()), this, SLOT(slot_map()));
  connect(map_3, SIGNAL(clicked()), this, SLOT(slot_map()));
  connect(map_4, SIGNAL(clicked()), this, SLOT(slot_map()));

  connect(play, SIGNAL(clicked()), myscene, SLOT(slot_play()));
  connect(stop, SIGNAL(clicked()), myscene, SLOT(slot_stop()));

  connect(quitter, SIGNAL(clicked()), this, SLOT(slot_quit()));

  return group_box;
}

void MainWindow::slot_pleinecran() {
  qDebug() << "[CONNEXION] : Changement du mode de l'écran en cours ...";
  this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
  qDebug() << "[CONNEXION] : Appel de la fonction pleinecran_myscene() ...";
  myscene->pleinecran_myscene();
}

void MainWindow::slot_ia() {
  qDebug() << "[CONNEXION] : Changement du niveau de l'intelligence artificielle ...";
  if (ia_1->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 1 choisi ...";
    myscene->setIA(IA_NIVEAU_1);
  } else if (ia_2->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 2 choisi ...";
    myscene->setIA(IA_NIVEAU_2);
  } else if (ia_3->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 3 choisi ...";
    myscene->setIA(IA_NIVEAU_3);
  } else {
    qDebug() << "[CONNEXION] : Niveau 1 par défaut ...";
    myscene->setIA(IA_NIVEAU_1);
  }
}

void MainWindow::slot_map() {
  qDebug() << "[CONNEXION] : Changement du niveau de la map ...";
  if (map_1->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 1 choisi ... Map Simple ...";
    myscene->setMap(1);
  } else if (map_2->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 2 choisi ... Obstacle ...";
    myscene->setMap(2);
  } else if (map_3->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 3 choisi ... Teleporter ...";
    myscene->setMap(3);
  } else if (map_4->isChecked()) {
    qDebug() << "[CONNEXION] : Niveau 4 choisi ... The Big Wall ...";
    myscene->setMap(4);
  } else {
    qDebug() << "[CONNEXION] : Niveau 1 par défaut ... Map Simple ...";
    myscene->setMap(1);
  }
}

void MainWindow::slot_quit() {
  qDebug() << "[SUCCES] : Fermeture de l'application.";
  exit(EXIT_SUCCESS);
}
