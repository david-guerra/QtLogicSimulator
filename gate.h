#pragma once
#include "pin.h"
#include <QBrush>
#include <QGraphicsRectItem>
#include <QObject>
#include <QPen>
#include <QPainter>
#include <cstdlib>
#include <vector>

class Gate : public QObject, public QGraphicsRectItem {
  Q_OBJECT
public:
  enum class GateType { AND, OR, NOT };
  Q_ENUM(GateType)

  explicit Gate(GateType type, QObject *parent = nullptr)
      : QObject(parent), QGraphicsRectItem(0, 0, 50, 50), m_type(type) {

    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);

    // Customize based on Type
    switch (m_type) {
    case GateType::AND:
      this->setBrush(QBrush(Qt::red));
      this->numInputPins = 2;
      this->name = "AND";
      break;
    case GateType::OR:
      this->setBrush(QBrush(Qt::blue));
      this->numInputPins = 2;
      this->name = "OR";
      break;
    case GateType::NOT:
      this->setBrush(QBrush(Qt::green));
      this->numInputPins = 1;
      this->name = "NOT";
      break;
    }

    this->numOutputPins = 1;
    updateInputPin();
    updateOutputPin();
  }
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        QGraphicsRectItem::paint(painter, option, widget);
        painter->setPen(Qt::white);
        painter->drawText(boundingRect(), Qt::AlignCenter, name);
    }

protected:
  GateType m_type;
  QString name;
  QColor gateColor;
  int numInputPins, numOutputPins;
  std::vector<Pin *> inputPin;
  std::vector<Pin *> outputPin;

  void setColor(const QColor &newColor) {
    this->gateColor = newColor;
    this->setBrush(QBrush(gateColor));
  }
  void updateInputPin() {
    int v_sz = inputPin.size();
    if (v_sz < this->numInputPins) {
      for (int i = v_sz; i < numInputPins; i++) {
        Pin *newPin = new Pin(Pin::PinType::Input, this);
        inputPin.push_back(newPin);

        int spacing = rect().height() / (numInputPins + 1);
        int yPos = spacing * (i + 1);
        newPin->setPos(0, yPos);
      }
    } else if (v_sz > this->numInputPins) {
      for (int i = this->numInputPins; i < v_sz; i++) {
        delete inputPin.back();
        inputPin.pop_back();
      }
    }
  }
  void updateOutputPin() {
    int v_sz = outputPin.size();
    if (v_sz < this->numOutputPins) {
      for (int i = v_sz; i < numOutputPins; i++) {
        Pin *newPin = new Pin(Pin::PinType::Output, this);
        outputPin.push_back(newPin);

        newPin->setPos(rect().width(), rect().height() / 2);
      }
    } else if (v_sz > this->numOutputPins) {
      for (int i = this->numOutputPins; i < v_sz; i++) {
        delete outputPin.back();
        outputPin.pop_back();
      }
    }
  }
};
