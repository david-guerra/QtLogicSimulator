#include "pin.h"
#include "wire.h"

QVariant Pin::itemChange(GraphicsItemChange change, const QVariant &value) {
  if (change == ItemScenePositionHasChanged) {
    for (Wire *wire : m_wires) {
      if (wire)
        wire->updatePath();
    }
  }
  return QGraphicsEllipseItem::itemChange(change, value);
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    Wire *wire = new Wire(this, nullptr);
    wire->setDragPos(event->scenePos());
    scene()->addItem(wire);
    event->accept();
  } else {
    QGraphicsEllipseItem::mousePressEvent(event);
  }
}

void Pin::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (!m_wires.empty() && m_wires.back()->parentItem() == nullptr) {
    Wire *currentWire = m_wires.back();
    currentWire->setDragPos(event->scenePos());
    event->accept();
  } else {
    QGraphicsEllipseItem::mouseMoveEvent(event);
  }
}

void Pin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    bool wireHandled = false;
    if (!m_wires.empty()) {
      Wire *currentWire = m_wires.back();
      if (currentWire->parentItem() == nullptr) {
        wireHandled = true;
        QList<QGraphicsItem *> items = scene()->items(event->scenePos());
        Pin *targetPin = nullptr;
        for (QGraphicsItem *item : items) {
          if (item != this && (targetPin = dynamic_cast<Pin *>(item))) {
            break;
          }
        }

        if (targetPin && isCompatible(targetPin)) {
          currentWire->setEndPin(targetPin);
        } else {
          delete currentWire;
        }
      }
    }
    if (wireHandled) {
      event->accept();
      return;
    }
  }
  QGraphicsEllipseItem::mouseReleaseEvent(event);
}
