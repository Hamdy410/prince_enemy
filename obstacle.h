#ifndef OBSTACLE_H
#define OBSTACLE_H
#include<QGraphicsTextItem>
#include<QGraphicsItem>
#include<QObject>
#include<QGraphicsItem>
#include<QGraphicsRectItem>
#include<QList>
#include<QPixmap>
#include<QRectF>
#include<QPaintEvent>

class player;
class Obstacle : public QObject, public QGraphicsPixmapItem
{
public:
    Q_OBJECT


public:
    Obstacle(const QPointF& pos, bool solid, bool visible,
             bool damaging);
    virtual ~Obstacle();

    virtual void onCollide(player* player);
    bool isSolid() const;
    bool isDamaging() const;
    bool isVisible() const;
    virtual void Activate();
    virtual void Update(player* player);
    QPointF m_pos;
    bool m_solid;
    bool m_visible;
    bool m_damaging;

};

#endif // OBSTACLE_H
