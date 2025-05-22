#ifndef COIN_H
#define COIN_H

#include "obstacle.h"
#include "player.h"
#include <QPainter>
#include <QPixmap>

class Coin : public Obstacle
{
    Q_OBJECT

public:
    explicit Coin(const QPointF& pos, int value = 10);
    ~Coin();

    // Override base class methods
    void Update(player* player) override;
    void onCollide(player* player) override;
    void render(QPainter* painter);

    // Coin-specific methods
    bool isCollected() const { return m_collected; }
    int getValue() const { return m_value; }
    QRectF boundingRect() const;
    QRectF collisionRect() const;

    // Static constants
    static const int COIN_WIDTH = 24;
    static const int COIN_HEIGHT = 24;

private:
    bool m_collected;
    int m_value;
    QPixmap m_coinImage;

    void loadCoinImage();

signals:
    void coinCollected(int value);
};

#endif // COIN_H
