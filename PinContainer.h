#pragma once
#include "pin.h"
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPen>

class PinContainer : public QObject, public QGraphicsEllipseItem {

  Q_OBJECT
public:
  enum class PortType { IN, OUT };
  Q_ENUM(PortType)
  explicit PinContainer(PortType type, QObject *parent = nullptr)
      : m_type(type), QObject(parent), QGraphicsEllipseItem(0, 0, 30, 30) {
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);
    switch (m_type) {
    case PortType::IN:
      this->setBrush(QBrush(Qt::red));
      this->numOutputPins = 1;
      this->numInputPins = 0;
      this->name = "IN";
      break;
    case PortType::OUT:
      this->setBrush(QBrush(Qt::blue));
      this->numInputPins = 1;
      this->numOutputPins = 0;
      this->name = "OUT";
      break;
    }
    setPin();
  }

protected:
  PortType m_type;
  QString name;
  int numOutputPins, numInputPins;
  Pin *actualPin;
  void setPin() {
    if (numOutputPins > 0) {
      actualPin = new Pin(Pin::PinType::Output, this);
      actualPin->setPos(rect().width(), rect().height() / 2);
    } else {
      actualPin = new Pin(Pin::PinType::Input, this);
      actualPin->setPos(-5, rect().height() / 2);
    }
  }
};
