#include "player.h"
#include "tile.h"
#include "health.h"
#include "score.h"
#include "pressuretile.h"

#include <QTransform>
#include <QPainter>
#include <QPixmap>
#include <QList>
#include <QDebug>

player::player(bool right, int health, QObject* parent)
    : QObject(parent),
    m_health(health),
    statue(right ? StillRight : StillLeft),
    m_x(100), m_y(100), groundy(100),
    frame(0),isCrouching(false),
    isHopping(0), isJumping(0),isFalling(true),RightFacingDirection(right),damage_of_falling(0),falling_distance(0)
    ,m_healthBar(new Health(m_health)), m_scoreBar(new Score)
{
    QPixmap SpriteSheet(":/images/Prince_Spritesheet.png");
    double width = SpriteSheet.width() / 14.0;
    double height = SpriteSheet.height() / 38.0;
    // Standing frames
    currentImageRight = SpriteSheet.copy(0, 0, width, height);
    QTransform transform;
    transform.scale(-1, 1);
    currentImageLeft = currentImageRight.transformed(transform);

    // Walk right/left
    QList<QPixmap> walkright, walkleft;
    int x = 0;
    for (int i = 0; i < 14; ++i) {
        QPixmap f = SpriteSheet.copy(x, height, width, height);
        walkright << f;
        walkleft << f.transformed(transform);
        x += width;
    }
    animationFrames << walkright << walkleft;

    // Hop right/left
    QList<QPixmap> hopright, hopleft;
    x = 0;
    for (int i = 0; i < 14; ++i) {
        QPixmap f = SpriteSheet.copy(x, 7 * height, width, height);
        hopright << f;
        hopleft << f.transformed(transform);
        x += width;
    }
    animationFrames << hopright << hopleft;

    // Jump right/left
    QList<QPixmap> jumpright, jumpleft;
    x = 0;
    for (int i = 0; i < 11; ++i) {
        QPixmap f = SpriteSheet.copy(x, 15 * height, width, height);
        jumpright << f;
        jumpleft << f.transformed(transform);
        x += width;
    }
    animationFrames << jumpright << jumpleft;

    QList<QPixmap> armRight, armLeft;
    x = 0;
    for (int i = 0; i < 5; i++) {
        QPixmap f = SpriteSheet.copy(x, 4 * height, width, height);
        armRight << f;
        armLeft << f.transformed(transform);
        x += width;
    }
    animationFrames << armRight << armLeft;

    QList<QPixmap> attackRight, attackLeft;
    x = 0;
    for (int i = 0; i < 8; i++) {
        QPixmap f = SpriteSheet.copy(x, 5 * height, width, height);
        attackRight << f;
        attackLeft << f.transformed(transform);
        x += width;
    }
    animationFrames << attackRight << attackLeft;
    QList<QPixmap>crouchRight, crouchLeft;
    x = width*3;
    for (int i = 0;i < 1; i++) {
        QPixmap f = SpriteSheet.copy(x, 0, width, height);
        crouchRight << f;
        crouchLeft << f.transformed(transform);
        x += width;
    }
    animationFrames<<crouchRight<<crouchLeft;
    groundy = m_y;
}

player::~player() {
    delete m_healthBar;
    delete m_scoreBar;
}

void player::handleKeyPress(QKeyEvent* event) {
    if (is_attacking || isFalling)
    {
        return;
    }
    if (event->key() == Qt::Key_Right) {
        if (isHopping == 2 || isJumping == 2 || isCrouching || is_attacking) return;
        if (isHopping == 1) {
            isFalling = false;
            isHopping = 2; isJumping=0; frame = 0; statue = HopRight; RightFacingDirection = true;
        } else if (isHopping == 0 && isJumping == 0) {
            statue = WalkRight; RightFacingDirection = true;
        }
    } else if (event->key() == Qt::Key_Left) {
        if (isHopping == 2 || isJumping == 2 || isCrouching || is_attacking) return;
        if (isHopping == 1) {
            isFalling = false;
            isHopping = 2; isJumping=0; frame = 0; statue = HopLeft; RightFacingDirection = false;
        } else if (isHopping == 0 && isJumping == 0) {
            statue = WalkLeft; RightFacingDirection = false;
        }
    } else if (event->key() == Qt::Key_Space) {
        if (isHopping != 2 && isJumping != 2 && !is_attacking && !isCrouching) {
            isHopping = 1; isJumping = 0;
        }
    } else if (event->key() == Qt::Key_Up) {
        if(isHopping!=2 && !isCrouching && !is_attacking && !isFalling){
            isFalling = false;
            isJumping=2;
            isHopping=0;
            if(!RightFacingDirection && !is_attacking && !isCrouching){
                statue = JumpLeft;
                RightFacingDirection = false;
            }else if(RightFacingDirection && !is_attacking && !isCrouching){
                statue = JumpRight;
                RightFacingDirection = true;
            }
            frame = 0;
            m_animCounter = 0;
        }
    }else if (event->key() == Qt::Key_Z) {
        if (!is_attacking && !isJumping && !isHopping && !isCrouching) {
            if(statue == StillLeft || statue==WalkLeft){
                statue = AttackLeft;
                RightFacingDirection = false;
            }else if(statue == StillRight || statue==WalkRight){
                statue = AttackRight;
                RightFacingDirection = true;
            }
            frame = 0;
            is_attacking = true;
            m_enemiesHitThisAttack.clear();
        }
    }else if(event->key()== Qt::Key_Down){
        if(!is_attacking && !isJumping && !isHopping){
            if(!RightFacingDirection){
                statue = crouchLeft;
            }else{
                statue = crouchRight;
            }
            frame = 0;
            isCrouching = true;
        }
    }
}

void player::handleKeyRelease(QKeyEvent* event) {
    if(is_attacking)
        return ;
    if (event->key() == Qt::Key_Right) {
        if (isHopping != 2 && isJumping != 2 && !is_attacking && !isCrouching)
            statue = StillRight;
        RightFacingDirection = true;
    } else if (event->key() == Qt::Key_Left) {
        if (isHopping != 2 && isJumping != 2  && !is_attacking && !isCrouching)
            statue = StillLeft;
        RightFacingDirection = false;
    } else if (event->key() == Qt::Key_Space) {
        if (isHopping != 2 && isJumping != 2 && !is_attacking && !isCrouching) {
            isHopping = 0; isJumping = 0; frame = 0;
        }
    } else if (event->key() == Qt::Key_Up) {
        if (isHopping != 2 && isJumping != 2 && !is_attacking && !isCrouching && !isFalling) {
            isHopping = 0; isJumping = 0; frame = 0;
        }
    }else if(event->key()==Qt::Key_Down){
        if(isCrouching){
            if(statue == crouchLeft){
                statue = StillLeft;
                RightFacingDirection = false;
            }else if(statue == crouchRight){
                statue = StillRight;
                RightFacingDirection = true;
            }
            frame=0;
            isCrouching=false;
        }
    }
}
void player::fall(const QList<tile*>& tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings){
    if(isJumping || isHopping==2)
        return ;
    if(!isFalling)
        return ;
    m_y+= 10;
    falling_distance+= 10;
    const float FALL_DAMAGE_THRESHOLD = 400.0f;
    if (falling_distance > FALL_DAMAGE_THRESHOLD) {
        damage_of_falling++;
    }
    checkCollisions(tiles,gates,choppers,walls,ceilings);
}
void player::update(const QList<tile*>& tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings) {
    if(isFalling && !isJumping && isHopping!=2){
        isJumping=0;
        isHopping=0;
        fall(tiles,gates,choppers,walls,ceilings);
        return ;
    }
    if(!isFalling)
        falling_distance=0;
    switch (statue) {
    case WalkRight:
        m_x += 3;
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[0].size()) frame = 0;
            m_animCounter = 0;
        }
        break;
    case WalkLeft:
        m_x -= 3;
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[1].size()) frame = 0;
            m_animCounter = 0;
        }
        break;
    case StillRight:
        frame = 0;
        break;
    case StillLeft:
        frame = 0;
        break;
    case HopRight:
        if (isHopping == 1) {
            isHopping = 2;
            frame = 0;
        }
        m_animCounter++;
        if (m_animCounter >= 4) {
            if (frame < 7) {
                m_x += 10;
                ++frame;
            } else if (frame < 14) {
                m_x += 10;
                ++frame;
            }else{
                isHopping = 0;
                frame = 0;
                statue=StillRight;
                RightFacingDirection=true;
            }
            m_animCounter = 0;
        }
        break;
    case HopLeft:
        if (isHopping == 1) {
            isHopping = 2;
            frame = 0;
        }
        m_animCounter++;
        if (m_animCounter >= 4) {
            if (frame < 7) {
                m_x -= 10;
                isHopping=2;
                ++frame;
            } else if (frame < 14) {
                m_x -= 10;
                isHopping=2;
                ++frame;
            } else {
                statue = StillLeft;
                isHopping = 0;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case JumpRight:
    case JumpLeft:
        m_animCounter++;
        isFalling=false;
        if (m_animCounter >= 2) {
            if (frame < 11) {
                m_y-= (20-frame); //this equation makes the jumping slower each time the player rises
                ++frame;
                isJumping=2;
                isFalling=false;
            }else {
                if(statue==JumpRight)
                    statue = StillRight;
                else
                    statue=StillLeft;
                isJumping=0;
                isFalling=true;
                isHopping = 0;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case AttackRight:
    case AttackLeft:
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[8 + (statue == AttackLeft ? 1 : 0)].size()) {
                is_attacking = false;
                m_enemiesHitThisAttack.clear();
                statue = (statue == AttackLeft || statue == StillLeft || statue == WalkLeft) ? StillLeft : StillRight;
                frame = 0;
            }
            m_animCounter = 0;
        }
        break;
    case crouchRight:
    case crouchLeft:
        m_animCounter++;
        if (m_animCounter >= m_animDelay) {
            frame++;
            if (frame >= animationFrames[10 + (statue == crouchLeft ? 1 : 0)].size()) {
                frame = 0;
            }
            m_animCounter = 0;
        }
    }

    // Always check collisions after movement/gravity
    checkCollisions(tiles,gates,choppers,walls,ceilings);

    if (isFalling && !isJumping && isHopping!=2) {
        if (RightFacingDirection)
            statue = StillRight;
        else if (!RightFacingDirection)
            statue = StillLeft;
        frame = 0;
    }

    // If landed, reset velocity and air state
}

void player::draw(QPainter* painter) {
    QPixmap framePixmap;
    switch (statue) {
    case WalkRight:
        framePixmap = animationFrames[0][frame % animationFrames[0].size()];
        break;
    case WalkLeft:
        framePixmap = animationFrames[1][frame % animationFrames[1].size()];
        break;
    case HopRight:
        framePixmap = animationFrames[2][qMin(frame, animationFrames[2].size() - 1)];
        break;
    case HopLeft:
        framePixmap = animationFrames[3][qMin(frame, animationFrames[3].size() - 1)];
        break;
    case JumpRight:
        framePixmap = animationFrames[4][qMin(frame, animationFrames[4].size() - 1)];
        break;
    case JumpLeft:
        framePixmap = animationFrames[5][qMin(frame, animationFrames[5].size() - 1)];
        break;
    case StillRight:
        framePixmap = currentImageRight;
        break;
    case StillLeft:
        framePixmap = currentImageLeft;
        break;
    case AttackRight:
        framePixmap = animationFrames[8][qMin(frame, animationFrames[8].size() - 1)];
        break;
    case AttackLeft:
        framePixmap = animationFrames[9][qMin(frame, animationFrames[9].size() - 1)];
        break;
    case crouchRight:
        framePixmap = animationFrames[10][qMin(frame,animationFrames[10].size()-1)];
        break;
    case crouchLeft:
        framePixmap = animationFrames[11][qMin(frame,animationFrames[11].size()-1)];
        break;
    default:
        framePixmap = currentImageRight;
        break;
    }

    painter->drawPixmap(QPointF(m_x, m_y + sinkOffset), framePixmap);

    // Debug: Draw bounding box and foot region
    //QRectF box = boundingRect();
    //painter->setPen(Qt::red);
    //painter->drawRect(box.translated(m_x, m_y));

    //painter->setBrush(QColor(255, 0, 0, 100));

    //painter->save();
    //painter->setPen(QPen(Qt::magenta, 2));
    //painter->setBrush(QColor(255, 0, 255, 90));
    //painter->drawRect(hurtRegion());
    //painter->restore();

    //QRectF hurt = hurtRegion();
    //painter->setPen(Qt::red);
    //painter->drawRect(hurt);
    //painter->restore();

    // QRectF hit = hitRegion();
    // if (!hit.isNull()) {
    //     painter->save();
    //     painter->setPen(QPen(Qt::green, 2));
    //     painter->setBrush(QColor(0, 255, 0, 80));
    //    painter->drawRect(hit);
    //     painter->restore();
    // }

    //QRectF feet = feetRegion();
    //if (!feet.isNull()) {
    //    painter->save();
    //    painter->setPen(QPen(Qt::magenta, 1 , Qt::DashLine));
    //    painter->drawRect(feet);
    //    painter->restore();
    //}
}

QRectF player::boundingRect() const {
    if(isCrouching){
        QPixmap framePixmap = animationFrames[10][0];
        if (!animationFrames.isEmpty() && !animationFrames[0].isEmpty())
            framePixmap = animationFrames[0][0];
        return QRectF(15, framePixmap.height()/2, framePixmap.width()/2, framePixmap.height()/2);
    }else{
        QPixmap framePixmap = currentImageRight;
        if (!animationFrames.isEmpty() && !animationFrames[0].isEmpty())
            framePixmap = animationFrames[0][0];
        return QRectF(25, 0, framePixmap.width()/2-20, framePixmap.height());
    }
}

QPointF player::pos() const {
    return QPointF(m_x, m_y);
}

void player::setPos(qreal x, qreal y) {
    m_x = x;
    m_y = y;
}

void player::setGround(qreal groundY) {
    groundy = groundY;
}

void player::checkCollisions(const QList<tile*> &tiles, const QList<Gate*>& gates,const QList<Chopper*>& choppers,const QList<wall*>& walls,const QList<ceiling*>& ceilings) {
    if(isHopping==2 && isJumping==2) //to jump without hitting the ground
        return;
    bool touchedTile=false;
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    //check for gates
    for (Gate* g: gates) {
        QRectF gateBox = g->boundingRect().translated(g->pos().x(), g->pos().y());
        if (playerBox.intersects(gateBox) && !g->isOpen()) {
            if(playerBox.right()>=((gateBox.left()+gateBox.right())/2+20) && (statue==StillRight || statue==WalkRight || statue==HopRight || statue==JumpRight)){
                m_x = gateBox.left()+16;
            }else if(playerBox.left()>=((gateBox.left()+gateBox.right())/2-20) && (statue==StillLeft || statue==WalkLeft || statue==HopLeft || statue==JumpLeft)){
                m_x = gateBox.right()-16;
            }
        }
    }
    for (wall* w: walls) {
        QRectF wallBox = w->boundingRect();
        if (playerBox.intersects(wallBox)) {
            float overlapLeft = playerBox.right() - wallBox.left();
            float overlapRight = wallBox.right() - playerBox.left();
            float minOverlap = qMin(overlapRight,overlapLeft);
            if(minOverlap==overlapLeft){
                 m_x = wallBox.left()+19;
            }else{
                m_x = wallBox.right()-19;
            }
        }
    }
    for(Chopper* c : choppers){
        QRectF chopperBox  = QRectF(c->pos().x()+10,c->pos().y(),c->boundingRect().width()-10,c->boundingRect().height());
        if(chopperBox.intersects(playerBox)){
            c->onCollide(this);
        }
    }
    // 1. Check for landing on top of a tile
    for (tile* t: tiles) {
        QRectF tileBox = t->boundingRect();
        float overlapLeft = playerBox.right() - tileBox.left();
        float overlapRight = tileBox.right() - playerBox.left();
        float overlapTop = playerBox.bottom() - tileBox.top();
        float overlapBottom = tileBox.bottom() - playerBox.top();
        float minOverlap = qMin(qMin(overlapLeft, overlapRight), qMin(overlapTop, overlapBottom));

        if (playerBox.intersects(tileBox)) {
            touchedTile=true;
            PressureTile *pt = dynamic_cast<PressureTile*>(t);
            if (pt && feetRegion().intersects(tileBox)) {
                pt->setPressed(!pt->isPressed());
            }
            if (minOverlap == overlapTop && isFalling) {
                // Landed from above
                m_y = t->pos().y() - playerBox.height();
                groundy = m_y;
                isFalling=false;
                takeDamage(damage_of_falling);
                damage_of_falling=0;
                break;
            }
            // TODO: Add ledge grab and side collision logic here if desired
        }
    }
    for (ceiling* c: ceilings) {
        QRectF ceilingBox = c->boundingRect();
        float overlapTop = playerBox.bottom() - ceilingBox.top();
        float overlapBottom = ceilingBox.bottom() - playerBox.top();
        float minOverlap = qMin(overlapTop,overlapBottom);

        if (playerBox.intersects(ceilingBox)) {
            if (minOverlap == overlapBottom) {
                isFalling = true;
                isJumping=0;
                isHopping=0;
                if (RightFacingDirection)
                    statue = StillRight;
                else if (!RightFacingDirection)
                    statue = StillLeft;
            }
            // TODO: Add ledge grab and side collision logic here if desired
        }
    }

    if(!touchedTile && !isFalling){
        isFalling = true;
    }

}

void player::takeDamage(int amount) {
    m_health -= amount;
    if (m_health < 0) m_health = 0;
    m_healthBar->decrease(amount);
}

QRectF player::hurtRegion() const {
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    qreal centerX = playerBox.left() + playerBox.width() / 2.0;
    qreal hurtX = centerX - HURT_REGION_WIDTH / 2.0;
    if(!isCrouching)
        return QRectF(hurtX+10, playerBox.top()+25, HURT_REGION_WIDTH-20, playerBox.height()-25);
    else
        return QRectF(hurtX, playerBox.top()+15, HURT_REGION_WIDTH, playerBox.height()-15);
}

QRectF player::hitRegion() const {
    QRectF playerBox = boundingRect().translated(m_x, m_y + sinkOffset);
    int swordLength = 20;
    if (statue == AttackRight) {
        return QRectF(playerBox.right(), playerBox.top() + playerBox.height() * 0.5, swordLength, playerBox.height() * 0.2);
    } else if (statue == AttackLeft) {
        return QRectF(playerBox.left() - swordLength, playerBox.top() + playerBox.height() * 0.5,
                      swordLength, playerBox.height() * 0.2);
    }

    return QRectF();
}

QRectF player::feetRegion() const {
    if(isCrouching){
        QRectF box = player::boundingRect();
        const qreal feetHeight = 9;
        const qreal widthFraction = 0.2;
        const qreal feetWidth = box.width() * widthFraction;

        const qreal xOffset = m_x + box.x() + (box.width() - feetWidth) / 2;

        const qreal yOffset = m_y + box.height() + 30;

        return QRectF(
            xOffset,
            yOffset,
            feetWidth,
            feetHeight);
    }else{
        QRectF box = player::boundingRect();
        const qreal feetHeight = 9;
        const qreal widthFraction = 0.2;
        const qreal feetWidth = box.width() * widthFraction;

        const qreal xOffset = m_x + box.x() + (box.width() - feetWidth) / 2;

        const qreal yOffset = m_y + box.height() - feetHeight + 4;

        return QRectF(
            xOffset,
            yOffset,
            feetWidth,
            feetHeight);
    }
}
