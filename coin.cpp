#include "coin.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

Coin::Coin(const QPointF& pos, int value)
    : Obstacle(pos, false, true, false), // Not solid, visible, not damaging
    m_collected(false),
    m_value(value)
{
    loadCoinImage();
}

Coin::~Coin()
{
    // Nothing special to clean up
}

void Coin::loadCoinImage()
{
    // Try to load your coin image - REPLACE with your actual image path
    m_coinImage = QPixmap(":/images/mcoins.jpg");

    if (m_coinImage.isNull()) {
        // Fallback: Create a simple coin if image not found
        qDebug() << "Coin image not found, creating simple fallback";

        m_coinImage = QPixmap(COIN_WIDTH, COIN_HEIGHT);
        m_coinImage.fill(Qt::transparent);

        QPainter painter(&m_coinImage);
        painter.setRenderHint(QPainter::Antialiasing);

        // Simple golden circle
        QRadialGradient gradient(COIN_WIDTH/2, COIN_HEIGHT/2, COIN_WIDTH/2);
        gradient.setColorAt(0, QColor(255, 215, 0));    // Gold center
        gradient.setColorAt(0.7, QColor(218, 165, 32)); // Darker gold
        gradient.setColorAt(1, QColor(184, 134, 11));   // Dark gold edge

        painter.setBrush(QBrush(gradient));
        painter.setPen(QPen(QColor(139, 69, 19), 2));
        painter.drawEllipse(2, 2, COIN_WIDTH-4, COIN_HEIGHT-4);

        // Add "$" symbol
        painter.setPen(QPen(QColor(139, 69, 19), 2));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(QRect(0, 0, COIN_WIDTH, COIN_HEIGHT), Qt::AlignCenter, "$");
    }
    else {
        // Scale the loaded image to our desired size
        if (m_coinImage.width() != COIN_WIDTH || m_coinImage.height() != COIN_HEIGHT) {
            m_coinImage = m_coinImage.scaled(COIN_WIDTH, COIN_HEIGHT,
                                             Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
}

void Coin::Update(player* player)
{
    if (m_collected || !player) return;

    // Check for collision with player
    QRectF playerRect = player->boundingRect().translated(player->pos());
    QRectF coinRect = collisionRect();

    if (playerRect.intersects(coinRect)) {
        onCollide(player);
    }
}

void Coin::onCollide(player* player)
{
    if (m_collected || !player) return;

    m_collected = true;

    // Add points to player's score
    player->scoreBar()->increase(m_value);

    // Emit signal for any additional handling (like sound effects)
    emit coinCollected(m_value);
}

void Coin::render(QPainter* painter)
{
    if (m_collected) return; // Don't draw if collected

    // Simply draw the coin image at its position
    painter->drawPixmap(m_pos, m_coinImage);
}

QRectF Coin::boundingRect() const
{
    return QRectF(0, 0, COIN_WIDTH, COIN_HEIGHT);
}

QRectF Coin::collisionRect() const
{
    // Slightly smaller collision box for better gameplay feel
    const int margin = 2;
    return QRectF(m_pos.x() + margin, m_pos.y() + margin,
                  COIN_WIDTH - 2*margin, COIN_HEIGHT - 2*margin);
}
