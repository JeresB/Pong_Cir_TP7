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

  //QSlider *vitesse = new QSlider(Qt::Vertical, this);
  //vitesse->setRange(0, 10);
  //vitesse->setGeometry(10, 60, 150, 20);
  plein_ecran = new QPushButton("Plein Ecran", this);
  niveau_ia = new QLabel("Niveau de l'IA", this);
  ia_1 = new QRadioButton("Niveau 1", this);
  ia_2 = new QRadioButton("Niveau 2", this);
  ia_3 = new QRadioButton("Niveau 3", this);
  // ia_1->setText("Niveau 1");
  //niveau_ia->addButton(ia_1);
  quitter = new QPushButton("Quitter", this);

  box_control = new QVBoxLayout;
    box_control->addWidget(plein_ecran);
    //box_control->addWidget(vitesse);
    box_control->addWidget(niveau_ia);
    box_control->addWidget(ia_1);
    box_control->addWidget(ia_2);
    box_control->addWidget(ia_3);
    box_control->addWidget(quitter);
    box_control->addStretch(1);
    group_box->setLayout(box_control);

  //connect(vitesse, SIGNAL(valueChanged(int)), myscene, SLOT(slot_setVitesse(int)));
  connect(plein_ecran, SIGNAL(clicked()), this, SLOT(slot_pleinecran()));
  connect(ia_1, SIGNAL(clicked()), this, SLOT(slot_ia()));
  connect(ia_2, SIGNAL(clicked()), this, SLOT(slot_ia()));
  connect(ia_3, SIGNAL(clicked()), this, SLOT(slot_ia()));
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
