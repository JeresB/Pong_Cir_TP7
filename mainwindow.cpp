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

  qbl_general->addWidget(BuildGroupBoxControle());
  qbl_general->addWidget(myview);

  menuFichier = menuBar()->addMenu(tr("&Fichier"));
}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  QGroupBox *qgb = new QGroupBox(tr("Contrôle"));
  QPushButton *pleinEcran = new QPushButton("Plein Ecran", this);

  connect(pleinEcran, SIGNAL(clicked()), myscene, SLOT(slot_pleinecran()));

  return qgb;
}

int MainWindow::getPleinEcran() {
  return myscene->getPleinEcran();
}
