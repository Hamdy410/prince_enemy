/*
  Base class for all obstacles in the game world, handling collision, visibility, and behavior.
 */

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

    // Called when a player collides with the obstacle.
    virtual void onCollide(player* player);
    bool isSolid() const;

    // Returns true if the obstacle causes damage.
    bool isDamaging() const;
    bool isVisible() const;
    // Called when the obstacle is activated (optional override).
    virtual void Activate();
    // Called to update obstacle behavior each frame (optional override).
    virtual void Update(player* player);
    QPointF m_pos;
    bool m_solid;
    bool m_visible;
    bool m_damaging;

};

#endif // OBSTACLE_H
