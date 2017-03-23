#include "mainwindow.h"
#include "myscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle("Pong");

  widget_general = new QWidget;
  QHBoxLayout *qbl_general = new QHBoxLayout;

  widget_general->setLayout(qbl_general);

  this->setCentralWidget(widget_general);

  //qbl_general->addWidget(BuildGroupBoxControle());


  myscene = new MyScene(this);
  myview = new QGraphicsView(myscene, this);

  qbl_general->addWidget(myview);

  menuFichier = menuBar()->addMenu(tr("&Fichier"));

}

MainWindow::~MainWindow(){}

QGroupBox *MainWindow::BuildGroupBoxControle() {
  QGroupBox *qgb = new QGroupBox(tr("Contrôle"));
  return qgb;
}
