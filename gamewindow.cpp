#include "gamewindow.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_debugMode(true),
    m_frameCounter(0), m_fps(0)
{
    setWindowTitle("Enemy Game");
    resize(640, 480);

    initializeGame();
    m_fpsTimer.start();
}

GameWindow::~GameWindow() {
    m_gameTimer.stop();
}

void GameWindow::initializeGame() {
    for (Enemy* enemy : m_enemies) {
        delete enemy;
    }
    m_enemies.clear();

    m_player = new QGraphicsRectItem(0, 0, 32, 64);
    m_player->setPos(width() / 2, height() / 2);

    createTiles();

    QList<QList<QGraphicsItem*>> platforms;
    QList<QGraphicsItem*> currentPlatform;

    for (int i = 0; i < m_tiles.size(); i++) {
        tile* currentTile = m_tiles[i];

        if (i == 0 || (qAbs(currentTile->pos().x() - m_tiles[i - 1]->pos().x()) <= 60 &&
                       currentTile->pos().y() == m_tiles[i-1]->pos().y()))
            currentPlatform.append(currentTile);
        else {
            if (!currentPlatform.isEmpty()) {
                platforms.append(currentPlatform);
                currentPlatform.clear();
            }
            currentPlatform.append(currentTile);
        }

        if (currentTile->hasEnemy()) {
            Enemy* enemy = new Enemy(this);
            if (enemy->initialize(":/sprites/enemy_sprite.png", 64, 64)) {
                enemy->setPlayer(m_player);

                QList<QGraphicsItem*> platformTiles = currentPlatform;
                enemy->setTiles(platformTiles);
                enemy->setPosition(QPoint(currentTile->pos().x(),
                                          currentTile->pos().y() - enemy->boundingRect().height() + enemy->ENEMY_TILE_OVERLAP));
                enemy->startPatrolling();
                m_enemies.append(enemy);

                connect(enemy, &Enemy::positionChanged, this, [this] () {
                    update();
                });
                connect(enemy, &Enemy::visualChanged, this, [this](){
                    update();
                });
                connect(enemy, &Enemy::died, this, [this, enemy, platformTiles]() {
                    QTimer::singleShot(3000, this, [this, enemy, platformTiles]() {
                        if (!platformTiles.isEmpty()) {
                            QGraphicsItem* firstTile = platformTiles.first();
                            enemy->setPosition(QPoint(firstTile->pos().x(), firstTile->pos().y() - enemy->boundingRect().height()));
                        }
                        enemy->m_alive = true;
                        enemy->setState(Enemy::WALKRIGHT);
                    });
                });
            }
        }
    }

    if (!currentPlatform.isEmpty()) {
        platforms.append(currentPlatform);
    }

    m_gameTimer.setInterval(16);
    connect(&m_gameTimer, &QTimer::timeout, this, &GameWindow::updateGame);
    m_gameTimer.start();
}

void GameWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    // Draw tiles
    for (tile* t : m_tiles) {
        painter.drawPixmap(t->pos(), t->pixmap());

        if (m_debugMode) {
            painter.setPen(QPen(Qt::green, 2));
            painter.setBrush(Qt::transparent);
            painter.drawRect(t->boundingRect().translated(t->pos()));
        }
    }

    // Draw the player
    painter.fillRect(m_player->boundingRect().translated(m_player->pos()), Qt::blue);


    // Draw Enemies
    for (Enemy* enemy : m_enemies) {
        enemy->render(&painter);
    }


    m_frameCounter++;
    if (m_fpsTimer.elapsed() >= 1000) {
        m_fps = m_frameCounter;
        m_frameCounter = 0;
        m_fpsTimer.restart();
    }

    if (m_debugMode) drawDebugInfo(&painter);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    Enemy* m_enemy = m_enemies.isEmpty() ? nullptr : m_enemies.first();

    switch (event->key()) {
    case Qt::Key_D:
        m_enemy->setState(Enemy::WALKRIGHT);
        break;
    case Qt::Key_A:
        m_enemy->setState(Enemy::WALKLEFT);
        break;
    case Qt::Key_R:
        m_enemy->setState(Enemy::ATTACKRIGHT);
        break;
    case Qt::Key_L:
        m_enemy->setState(Enemy::ATTACKLEFT);
        break;
    case Qt::Key_K:
        m_enemy->setState(Enemy::DIERIGHT);
        break;
    case Qt::Key_J:
        m_enemy->setState(Enemy::DIELEFT);
        break;
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        m_enemy->setAnimationSpeed(m_enemy->animationSpeed() + 5);
        qDebug() << "Animation speed: " << m_enemy->animationSpeed() << "FPS";
        break;
    case Qt::Key_Minus:
        if (m_enemy->animationSpeed() > 5) {
            m_enemy->setAnimationSpeed(m_enemy->animationSpeed() - 5);
        }
        qDebug() << "Animation Speed: " << m_enemy->animationSpeed() << "FPS";
        break;
    case Qt::Key_T:
        toggleDebugMode();
        break;
    case Qt::Key_Space:
        break;
    case Qt::Key_Escape:
        close();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }

    QMainWindow::keyPressEvent(event);
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        QMainWindow::keyReleaseEvent(event);
        return;
    }

    QMainWindow::keyReleaseEvent(event);
}

void GameWindow::resizeEvent(QResizeEvent *event) {
    QMap<Enemy*, QList<QGraphicsItem*>> enemyPlatforms;

    createTiles();

    QList<QList<QGraphicsItem*>> platforms;
    QList<QGraphicsItem*> currentPlatform;

    for (int i = 0; i < m_tiles.size(); i++) {
        tile* currentTile = m_tiles[i];

        if (i == 0 || (qAbs(currentTile->pos().x() - m_tiles[i-1]->pos().x()) <= 60 &&
                       currentTile->pos().y() == m_tiles[i-1]->pos().y())) {
            currentPlatform.append(currentTile);
        } else {
            if (!currentPlatform.isEmpty()) {
                platforms.append(currentPlatform);
                currentPlatform.clear();
            }
            currentPlatform.append(currentTile);
        }
    }

    if (!currentPlatform.isEmpty()) {
        platforms.append(currentPlatform);
    }

    int enemyIndex = 0;
    for (int i = 0; i < platforms.size() && enemyIndex < m_enemies.size(); i++) {
        bool platformHasEnemy = false;
        for (QGraphicsItem* item : platforms[i]) {
            tile* t = dynamic_cast<tile*>(item);
            if (t && t->hasEnemy()) {
                platformHasEnemy = true;
                break;
            }
        }

        if (platformHasEnemy && enemyIndex < m_enemies.size()) {
            m_enemies[enemyIndex]->setTiles(platforms[i]);
            if (!platforms[i].isEmpty()) {
                QGraphicsItem* firstTile = platforms[i].first();
                m_enemies[enemyIndex]->setPosition(QPoint(
                    firstTile->pos().x(),
                    firstTile->pos().y() - m_enemies[enemyIndex]->boundingRect().height() + Enemy::ENEMY_TILE_OVERLAP
                    ));
            }

            enemyIndex++;
        }
    }

    QMainWindow::resizeEvent(event);
}

void GameWindow::drawDebugInfo(QPainter *painter) {
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    QStringList debugInfo;
    debugInfo << QString("FPS: %1").arg(m_fps);

    if (!m_enemies.isEmpty()) {
        Enemy* firstEnemy = m_enemies.first();
        debugInfo << QString("State: %1").arg(stateToString(firstEnemy->m_currentState))
                  << QString("Position: (%1, %2)").arg(firstEnemy->position().x()).arg(firstEnemy->position().y())
                  << QString("Size: 64x64");
    }

    debugInfo << "D: Walk right | A: Walk left"
              << "R: Attack right | L: Attack left"
              << "K: Die right | J: Die left"
              << "+/-: Adjust Speed | T: toggle debug";

    debugInfo << QString("Enemies: %1").arg(m_enemies.size());

    QRect infoBox(10, 10, 250, 20 * debugInfo.size() + 10);
    painter->fillRect(infoBox, QColor(255, 255, 255, 200));
    painter->drawRect(infoBox);

    for (int i = 0; i < debugInfo.size(); i++) {
        painter->drawText(20, 30 + i * 20, debugInfo[i]);
    }
}

QString GameWindow::stateToString(Enemy::State state) const {
    switch (state) {
    case Enemy::WALKRIGHT: return "WALK RIGHT";
    case Enemy::WALKLEFT: return "WALK LEFT";
    case Enemy::DIELEFT: return "DIE LEFT";
    case Enemy::DIERIGHT: return "DIE RIGHT";
    case Enemy::ATTACKLEFT: return "ATTACK LEFT";
    case Enemy::ATTACKRIGHT: return "ATTACK RIGHT";
    default: return "Unknown";
    }
}

void GameWindow::updateGame() {
    for (Enemy* enemy : m_enemies) {
        if (enemy) {
            enemy->update(width());
        }
    }
}

QList<tile*> GameWindow::createTiles(int startX, int y, int count, int tileWidth, bool createEnemy, int overlap) {
    QList<tile*> tileList;

    for (int i = 0; i < count; i++) {
        bool tileHasEnemy = createEnemy && (i == 0);
        int x = startX + i * (tileWidth - overlap);
        tile* newTile = new tile(x, y, tileHasEnemy);
        tileList.append(newTile);
    }

    return tileList;
}

void GameWindow::createTiles() {
    for (tile* t : m_tiles) {
        delete t;
    }
    m_tiles.clear();

    QList<tile*> platform1 = createTiles(100, height() - 100, 10, 60, true, 28);
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 200, 3, 60, true, 28);
    m_tiles.append(platform2);
}
