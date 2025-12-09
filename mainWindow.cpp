#include "mainWindow.h"
#include "PinContainer.h"
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 800, 600);
  scene->setBackgroundBrush(Qt::lightGray);
  
  view = new QGraphicsView(scene);
  view->setRenderHint(QPainter::Antialiasing);
  setCentralWidget(view);
  resize(1024, 768);
  setWindowTitle("Logic Gate Simulator");

  createMenu();
}

void MainWindow::createMenu() {
  QToolBar *toolbar = addToolBar("Gates");
  addToolBar(Qt::LeftToolBarArea, toolbar);
  toolbar->setMovable(false);

  QAction *actAnd = toolbar->addAction("AND");
  actAnd->setToolTip("Add an AND Gate");
  connect(actAnd, &QAction::triggered, this,
          [this]() { spawnGate(Gate::GateType::AND); });
  QAction *actOr = toolbar->addAction("OR");
  actOr->setToolTip("Add an OR Gate");
  connect(actOr, &QAction::triggered, this,
          [this]() { spawnGate(Gate::GateType::OR); });
  QAction *actNot = toolbar->addAction("NOT");
  actNot->setToolTip("Add a NOT Gate");
  connect(actNot, &QAction::triggered, this,
          [this]() { spawnGate(Gate::GateType::NOT); });
  QAction *actIn = toolbar->addAction("IN");
  actIn->setToolTip("Add an Input Pin");
  connect(actIn, &QAction::triggered, this,
          [this]() { spawnPort(PinContainer::PortType::IN); });
  QAction *actOut = toolbar->addAction("OUT");
  actOut->setToolTip("Add an Output Pin");
  connect(actOut, &QAction::triggered, this,
          [this]() { spawnPort(PinContainer::PortType::OUT); });
}

void MainWindow::spawnGate(Gate::GateType type) {
  Gate *gate = new Gate(type);
  gate->setPos(100, 100);
  scene->addItem(gate);
}
void MainWindow::spawnPort(PinContainer::PortType type) {
  PinContainer *port = new PinContainer(type);
  port->setPos(100, 100);
  scene->addItem(port);
}
