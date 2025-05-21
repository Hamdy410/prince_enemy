#include "loosetile.h"
#include <QPixmap>
#include <QPainter>

LooseTile::LooseTile(int x, int y, bool hasEnemy, int width, int height)
    : tile(x, y - 2, hasEnemy, width, height),
    m_pressed(false),
    m_normalY(y - 2),
    m_pressedY(y),
    m_state(Idle),
    m_shakeCount(0)
{

    loadImages();
    m_animTimer = new QTimer();
    m_animTimer->setInterval(100);

    connect(m_animTimer, &QTimer::timeout, this, &LooseTile::advanceAnimation);

    m_disappearTimer = new QTimer();
    m_disappearTimer->setSingleShot(true);
    m_disappearTimer->setInterval(500); // 500ms total shaking time
    connect(m_disappearTimer, &QTimer::timeout, this, [this]() {
        m_state = Disappearing;
        m_animTimer->stop();
        setVisible(false);
        update();
    });

    setPos(x, m_normalY);
}

LooseTile::~LooseTile()
{

    delete m_idleImage;
    delete m_shaking1Image;
    delete m_shaking2Image;
    m_animTimer->stop();
    m_disappearTimer->stop();
}

void LooseTile::loadImages()
{
    m_idleImage = new QPixmap(":/images/Idle.png");

    m_shaking1Image = new QPixmap(":/images/shaking1.png");

    m_shaking2Image = new QPixmap(":/images/shaking2.png");
}

void LooseTile::setPressed(bool pressed) {
    if (m_pressed == pressed || m_state == Disappearing)
        return;

    m_pressed = pressed;

    if (pressed && m_state == Idle) {

        m_state = Shaking1;
        m_shakeCount = 0;
        m_animTimer->start();
        m_disappearTimer->start();
    }
}

QRectF LooseTile::activationRegion() const {
    QRectF tileBox = boundingRect();

    const qreal regionHeight = 4;
    const qreal widthFraction = 0.6;
    const qreal regionWidth = tileBox.width() * widthFraction;

    return QRectF(
        (tileBox.width() - regionWidth) / 2,
        0,
        regionWidth,
        regionHeight
        );
}

void LooseTile::startBreakSequence() {

    m_state = Shaking1;
    m_shakeCount = 0;

    m_animTimer->start();
    m_disappearTimer->start();
}

void LooseTile::advanceAnimation() {

    if (m_state == Shaking1) {
        m_state = Shaking2;
    } else if (m_state == Shaking2) {
        m_state = Shaking1;
    }


    m_shakeCount++;
    update();
}

void LooseTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    tile::paint(painter, option, widget);

    draw(painter);

    QRectF region = activationRegion();

    painter->setPen(QPen(Qt::cyan, 2, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(region);

    // Also draw a border around the whole tile
    QColor borderColor = Qt::blue;
    if (m_state == Shaking1 || m_state == Shaking2) {
        borderColor = Qt::yellow;
    } else if (m_state == Disappearing) {
        borderColor = Qt::red;
    }

    painter->setPen(QPen(borderColor, 2));
    painter->drawRect(boundingRect());
}

void LooseTile::draw(QPainter* painter) {
    QPixmap* currentFrame = nullptr;

    switch (m_state) {
    case Idle:
        currentFrame = m_idleImage;
        break;
    case Shaking1:
        currentFrame = m_shaking1Image;
        break;
    case Shaking2:
        currentFrame = m_shaking2Image;
        break;
    case Disappearing:
        return;
    }

    if (currentFrame) {
        painter->drawPixmap(0, 0, *currentFrame);
    }
}

