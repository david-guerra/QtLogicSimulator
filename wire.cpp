#include "wire.h"
#include "pin.h"
#include <QPainterPath>

Wire::Wire(Pin *start, Pin *end, QGraphicsItem *parent)
    : QObject(), QGraphicsPathItem(parent), m_startPin(start), m_endPin(end) {
  setPen(QPen(Qt::black, 2));
  setZValue(-1);

  if (m_startPin)
    m_startPin->addWire(this);
  if (m_endPin)
    m_endPin->addWire(this);

  updatePath();
}

Wire::~Wire() {
  if (m_startPin)
    m_startPin->removeWire(this);
  if (m_endPin)
    m_endPin->removeWire(this);
}

void Wire::updatePath() {
  if (!m_startPin)
    return;

  QPointF startPos = m_startPin->scenePos();
  QPointF endPos;

  if (m_endPin) {
    endPos = m_endPin->scenePos();
  } else {
    endPos = m_dragPos;
  }

  QPainterPath path;
  path.moveTo(startPos);

  double dx = endPos.x() - startPos.x();

  QPointF ctrl1(startPos.x() + dx * 0.5, startPos.y());
  QPointF ctrl2(endPos.x() - dx * 0.5, endPos.y());

  path.cubicTo(ctrl1, ctrl2, endPos);

  setPath(path);
}

void Wire::setDragPos(const QPointF &pos) {
  m_dragPos = pos;
  updatePath();
}

void Wire::setEndPin(Pin *end) {
  m_endPin = end;
  if (m_endPin) {
    m_endPin->addWire(this);
  }
  updatePath();
}
