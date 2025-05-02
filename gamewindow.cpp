#include "gamewindow.h"
#include "player.h"
#include "health.h"
#include "spikes.h"
#include "pressuretile.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_debugMode(true),
    m_frameCounter(0), m_fps(0)
{
    setWindowTitle("Enemy Game");
    resize(640, 480);
    m_fpsTimer.start();

    connect(&m_gameTimer, &QTimer::timeout, this, &GameWindow::updateGame);
}

GameWindow::~GameWindow() {
    m_gameTimer.stop();

    for (Enemy* enemy : m_enemies) delete enemy;
    for (tile* t: m_tiles) delete t;
    for (Spikes* spike : m_spikes) delete spike;
    delete m_player;
}

void GameWindow::initializeGame() {
    for (Enemy* enemy : m_enemies) {
        delete enemy;
    }
    m_enemies.clear();
    for (Spikes* spike : m_spikes) delete spike;
    m_spikes.clear();

    m_player = new player(true, this);

    createTiles();

    if (!m_tiles.isEmpty()) {
        tile* firstTile = m_tiles.first();
        int playerStartX = firstTile->pos().x();
        int playerStartY = firstTile->pos().y() - m_player->boundingRect().height();

        m_player->setPos(playerStartX, playerStartY);
        m_player->setGround(playerStartY);
    }

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
                enemy->setState(Enemy::WALKRIGHT);
                enemy->resetAnimation();

                enemy->setPlayer(nullptr);

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
                    // QTimer::singleShot(3000, this, [this, enemy, platformTiles]() {
                    //     if (!platformTiles.isEmpty()) {
                    //         QGraphicsItem* firstTile = platformTiles.first();
                    //         enemy->setPosition(QPoint(firstTile->pos().x(), firstTile->pos().y() - enemy->boundingRect().height()));
                    //     }
                    //     enemy->m_alive = true;
                    //     enemy->setState(Enemy::WALKRIGHT);
                    // });
                    m_player->scoreBar()->increase(10);
                });
            }
        }
    }

    if (!currentPlatform.isEmpty()) {
        platforms.append(currentPlatform);
    }

    m_gameTimer.setInterval(16);
    m_gameTimer.start();

    for (Enemy* enemy: m_enemies) {
        enemy->setPlayer(m_player);
    }
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

    // Draw Spikes
    for (Spikes* spike : m_spikes) {
        spike->render(&painter);
    }


    // Draw Enemies
    for (Enemy* enemy : m_enemies) {
        enemy->render(&painter);
    }

    // Draw gates
    for (Gate* gate : m_gates) {
        painter.drawPixmap(gate->pos(), gate->pixmap());

        if (m_debugMode) {
            painter.setPen(QPen(Qt::red, 2));
            painter.drawRect(gate->boundingRect().translated(gate->pos()));
        }
    }

    // Draw player
    m_player->draw(&painter);


    m_frameCounter++;
    if (m_fpsTimer.elapsed() >= 1000) {
        m_fps = m_frameCounter;
        m_frameCounter = 0;
        m_fpsTimer.restart();
    }

    if (m_debugMode) drawDebugInfo(&painter);

    m_player->healthBar()->draw(&painter, 20, 20, 200, 20);
    m_player->scoreBar()->draw(&painter, 20, 60);

    if (m_gameOver) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw semi-transparent black overlay
        painter.fillRect(rect(), QColor(0, 0, 0, 180));

        // Draw "Game Over" Text
        QFont mainFont("Arial", 48, QFont::Bold);
        painter.setFont(mainFont);
        painter.setPen(Qt::white);
        QString mainText = "Game Over";
        QRect textRect = rect();
        painter.drawText(textRect, Qt::AlignCenter, mainText);

        // Draw subtext just below it.
        QFont subFont("Arial", 20, QFont::Normal);
        painter.setFont(subFont);
        QString subText = "Press \"R\" to restart";

        // Calculate position: center horizontally and a bit below the main
        // text
        QFontMetrics mainMetrics(mainFont);
        int mainTextHeight = mainMetrics.boundingRect(mainText).height();
        QFontMetrics subMetrics(subFont);
        int subTextHeight = subMetrics.boundingRect(subText).height();

        int centerX = rect().center().x();
        int centerY = rect().center().y();

        int subTextY = centerY + mainTextHeight / 2 + subTextHeight + 10;
        QRect subTextRect(0, subTextY, rect().width(), subTextHeight + 10);
        painter.drawText(subTextRect, Qt::AlignHCenter | Qt::AlignTop, subText);
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    if (m_gameOver) {
        if (event->key() == Qt::Key_R) {
            m_gameOver = false;
            initializeGame();
            m_gameTimer.start();
            // --- Resize Workaround ---
            QSize orig = size();
            resize(orig.width(), orig.height() + 1);
            resize(orig);
            // -------------------------
            update();
        }

        return;
    }

    m_player->handleKeyPress(event);

    switch (event->key()) {
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
    if (event->isAutoRepeat() || m_gameOver) {
        QMainWindow::keyReleaseEvent(event);
        return;
    }

    m_player->handleKeyRelease(event);

    QMainWindow::keyReleaseEvent(event);
}

void GameWindow::resizeEvent(QResizeEvent *event) {

    QMap<Enemy*, QList<QGraphicsItem*>> enemyPlatforms;

    createTiles();

    if (!m_tiles.isEmpty()) {
        tile* firstTile = m_tiles.first();
        int playerStartX = firstTile->pos().x();
        int playerStartY = firstTile->pos().y() - m_player->boundingRect().height();

        m_player->setPos(playerStartX, playerStartY);
        m_player->setGround(playerStartY);
    }

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
    // Check for player health
    if (m_player->isDead() && !m_gameOver) {
        m_gameOver = true;
        m_gameTimer.stop();
        update();
    }

    for (Enemy* enemy : m_enemies) {
        if (enemy) {
            enemy->update(width());
        }
    }

    m_player->update(m_tiles);

    // --- Player attack Logic ---
    if (m_player->isAttacking()) {
        QRectF playerHit = m_player->hitRegion();
        for (Enemy* enemy : m_enemies) {
            if (enemy->isAlive() &&
                playerHit.intersects(enemy->hurtRegion()) &&
                !m_player->enemiesHitThisAttack().contains(enemy)) {
                enemy->takeDamage(1);
                m_player->enemiesHitThisAttack().insert(enemy);
            }
        }
    }

    for (Spikes* spike : m_spikes) {
        if (!spike || !m_player) continue;

        spike->Update(m_player);
        QRectF playerRect = m_player->hurtRegion();
        QRectF spikeRect = spike->hitRegion();

        if (playerRect.intersects(spikeRect))
            spike->onCollide(m_player);
    }

    update();
}

QList<tile*> GameWindow::createTiles(int startX, int y, int count,
                                      int tileWidth, bool createEnemy,
                                      int overlap, const QList<int>& spikeIndices,
                                      const QList<int>& pressureIndices,
                                      const QList<int>& gateIndices) {
    QList<tile*> tileList;

    for (int i = 0; i < count; i++) {
        bool tileHasEnemy = createEnemy && (i == 0);
        int x = startX + i * (tileWidth - overlap);

        tile* newTile = nullptr;
        if (pressureIndices.contains(i)) {
            newTile = new PressureTile(x, y, tileHasEnemy);
        } else {
            newTile = new tile(x, y, tileHasEnemy);
        }
        tileList.append(newTile);

        if (spikeIndices.contains(i)) {
            Spikes* spike = new Spikes(QPointF(x, y - Spikes::FRAME_HEIGHT + Spikes::SPIKE_SINK_OFFSET_Y));
            spike->setOffset(0, 6);
            m_spikes.append(spike);
        }

        if (gateIndices.contains(i)) {
            Gate* gate = new Gate(QPointF(x, y - 80 + Gate::SINK_OFFSET));
            m_gates.append(gate);
        }
    }

    return tileList;
}

void GameWindow::createTiles() {
    for (tile* t : m_tiles) {
        delete t;
    }
    m_tiles.clear();

    QList<tile*> platform1 = createTiles(100, height() - 100, 10, 60, true, 28, QList<int>{3, 5});
    m_tiles.append(platform1);

    QList<tile*> platform2 = createTiles(400, height() - 200, 3, 60, true, 28, QList<int>{1});
    m_tiles.append(platform2);

    QList<tile*> platform3 = createTiles(50, height() - 300, 5, 60, false, 28, QList<int>{2});
    m_tiles.append(platform3);
}
