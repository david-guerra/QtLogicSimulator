#pragma once
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPen>

class Wire;
class Pin : public QObject, public QGraphicsEllipseItem {
  Q_OBJECT
public:
  enum class PinType { Input, Output };
  Q_ENUM(PinType)
  explicit Pin(PinType type, QGraphicsItem *parent = nullptr)
      : QObject(nullptr), QGraphicsEllipseItem(-5, -5, 10, 10, parent),
        m_type(type) {
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setAcceptHoverEvents(true);

    if (m_type == PinType::Input) {
      this->setBrush(QBrush(Qt::yellow));
    } else {
      this->setBrush(QBrush(Qt::yellow));
    }
  }

  void setType(PinType type) { this->m_type = type; }
  PinType getType() const { return m_type; }

  bool isCompatible(Pin *other) const {
    if (this->m_type == other->m_type)
      return false;
    if (this->m_type == PinType::Input && !this->m_wires.empty())
      return false;
    if (other->m_type == PinType::Input && !other->m_wires.empty())
      return false;
    return true;
  }

  void addWire(Wire *wire) { m_wires.push_back(wire); }

  void removeWire(Wire *wire) {
    auto it = std::find(m_wires.begin(), m_wires.end(), wire);
    if (it != m_wires.end()) {
      m_wires.erase(it);
    }
  }

  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  PinType m_type;
  std::vector<Wire *> m_wires;
  bool pinValue;
};
