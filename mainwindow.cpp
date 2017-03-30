#include "mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Pong");

  widget_general = new QWidget;
  QHBoxLayout *qbl_general = new QHBoxLayout;

  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);

  myscene = new MyScene(this);
  myview = new QGraphicsView(myscene, this);
  myview->setCacheMode(QGraphicsView::CacheBackground);

  qbl_general->addWidget(BuildGroupBoxControle());
  qbl_general->addWidget(myview);

  action_reset = new QAction(tr("&Reset"), this);
  action_couleur = new QAction(tr("&Couleur"), this);
  menuFichier = menuBar()->addMenu(tr("&Fichier"));
  menuFichier->addAction(action_reset);
  menuFichier->addAction(action_couleur);

  connect(action_couleur, SIGNAL(triggered()), myscene, SLOT(slot_couleur()));
  connect(action_reset, SIGNAL(triggered()), myscene, SLOT(slot_reset()));
}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  QGroupBox *qgb = new QGroupBox(tr("Contrôle"));

  QSlider *vitesse = new QSlider(Qt::Vertical, this);
  QPushButton *pleinEcran = new QPushButton("Plein Ecran", this);
  QPushButton *quitter = new QPushButton("Quitter", this);

  vitesse->setRange(0, 10);
  vitesse->setGeometry(10, 60, 150, 20);

  QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pleinEcran);
    vbox->addWidget(vitesse);
    vbox->addWidget(quitter);
    vbox->addStretch(1);
    qgb->setLayout(vbox);


  connect(pleinEcran, SIGNAL(clicked()), this, SLOT(slot_pleinecran()));
  connect(vitesse, SIGNAL(valueChanged(int)), myscene, SLOT(slot_setVitesse(int)));
  connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

  return qgb;
}

void MainWindow::slot_pleinecran() {
  if (this->isFullScreen()) {
    this->show();
  } else {
    this->showFullScreen();
  }
}

int MainWindow::getPleinEcran() {
  return myscene->getPleinEcran();
}
