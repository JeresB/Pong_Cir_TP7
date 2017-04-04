#include "mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Pong"); // Nom de la fenêtre

  widget_general = new QWidget;
  QHBoxLayout *qbl_general = new QHBoxLayout;

  // Création du widget principale
  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);

  // Création de la scène de jeu
  myscene = new MyScene(this);
  myscene->setBackgroundBrush(QColor(13, 139, 242));
  myview = new QGraphicsView(myscene, this);

  qbl_general->addWidget(BuildGroupBoxControle());
  qbl_general->addWidget(myview);

  // Action permettant de reset le score des joueurs
  action_reset = new QAction(tr("&Reset"), this);

  // Action permettant de changer la couleur du fond
  action_couleur = new QAction(tr("&Couleur"), this);

  // Création du menu et ajout de nos actions
  menuFichier = menuBar()->addMenu(tr("&Fichier"));
  menuFichier->addAction(action_reset);
  menuFichier->addAction(action_couleur);

  connect(action_couleur, SIGNAL(triggered()), myscene, SLOT(slot_couleur()));
  connect(action_reset, SIGNAL(triggered()), myscene, SLOT(slot_reset()));
}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  group_box = new QGroupBox(tr("Contrôle"));

  plein_ecran = new QPushButton("Plein Ecran", this);

  niveau_ia = new QLabel("Niveau de l'IA", this);
  groupe_ia = new QButtonGroup(this);
  ia_1 = new QRadioButton("Niveau 1", this);
  ia_2 = new QRadioButton("Niveau 2", this);
  ia_3 = new QRadioButton("Niveau 3", this);
  groupe_ia->addButton(ia_1);
  groupe_ia->addButton(ia_2);
  groupe_ia->addButton(ia_3);

  niveau_map = new QLabel("Niveau de la map", this);
  groupe_map = new QButtonGroup(this);
  map_1 = new QRadioButton("Simple", this);
  map_2 = new QRadioButton("Obstacles", this);
  map_3 = new QRadioButton("The Big Wall", this);
  groupe_map->addButton(map_1);
  groupe_map->addButton(map_2);
  groupe_map->addButton(map_3);


  quitter = new QPushButton("Quitter", this);

  box_control = new QVBoxLayout;

    box_control->addWidget(plein_ecran);

    box_control->addWidget(niveau_ia);
    box_control->addWidget(ia_1);
    box_control->addWidget(ia_2);
    box_control->addWidget(ia_3);

    box_control->addWidget(niveau_map);
    box_control->addWidget(map_1);
    box_control->addWidget(map_2);
    box_control->addWidget(map_3);

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

  connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

  return group_box;
}

void MainWindow::slot_pleinecran() {
  this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
  myscene->pleinecran_myscene();
}

void MainWindow::slot_ia() {
  if (ia_1->isChecked()) {
    myscene->setIA(IA_NIVEAU_1);
  } else if (ia_2->isChecked()) {
    myscene->setIA(IA_NIVEAU_2);
  } else if (ia_3->isChecked()) {
    myscene->setIA(IA_NIVEAU_3);
  } else {
    myscene->setIA(IA_NIVEAU_1);
  }
}

void MainWindow::slot_map() {
  if (map_1->isChecked()) {
    myscene->setMap(1);
  } else if (map_2->isChecked()) {
    myscene->setMap(2);
  } else if (map_3->isChecked()) {
    myscene->setMap(3);
  } else {
    myscene->setMap(1);
  }
}
