#pragma once
#include "PinContainer.h"
#include "gate.h"
#include "pin.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
private slots:

  void spawnGate(Gate::GateType type);

  void spawnPort(PinContainer::PortType type);

private:
  void createMenu();

  QGraphicsScene *scene;
  QGraphicsView *view;
};
