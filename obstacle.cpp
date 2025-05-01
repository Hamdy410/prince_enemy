#include "obstacle.h"

Obstacle::Obstacle(const QPointF& pos, bool solid, bool visible,
                   bool damaging): QObject(), QGraphicsPixmapItem(), m_pos(pos), m_solid(solid), m_visible(visible),
    m_damaging(damaging) {}
Obstacle::~Obstacle() {}
bool Obstacle::isSolid() const{ return m_solid; }
bool Obstacle::isVisible() const {return m_visible;}
bool Obstacle::isDamaging() const {return m_damaging; }
void Obstacle:: Activate(){}
void Obstacle::Update(player* player){}
void Obstacle::onCollide(player *player){}
