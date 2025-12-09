#include <QGraphicsPathItem>
#include <QObject>
#include <QPen>

class Pin;

class Wire : public QObject, public QGraphicsPathItem {
  Q_OBJECT
public:
  Wire(Pin *start, Pin *end, QGraphicsItem *parent = nullptr);
  ~Wire();
  void updatePath();

  void setDragPos(const QPointF &pos);
  void setEndPin(Pin *end);

private:
  Pin *m_startPin;
  Pin *m_endPin;
  QPointF m_dragPos;
};
