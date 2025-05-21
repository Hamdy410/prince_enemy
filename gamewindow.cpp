#include "gamewindow.h"
#include "player.h"
#include "health.h"
#include "spikes.h"
#include "pressuretile.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_debugMode(false),
    m_frameCounter(0), m_fps(0)
{
    setWindowTitle("Enemy Game");
    resize(640, 463);
    m_fpsTimer.start();
    transitionX=450;
    transitionY=400;
    transitionWidth=20;
    transitionHeight=20;
    PositionPlayerx=0;
    PositionPlayery=0;
    total_health=15;
    transition = new Transition(transitionX,transitionY,transitionWidth,transitionHeight);
    Background=nullptr;
    connect(&m_gameTimer, &QTimer::timeout, this, &GameWindow::updateGame);
}

void GameWindow::getNextRoom(){}

GameWindow::~GameWindow() {
    m_gameTimer.stop();

    for (Enemy* enemy : m_enemies) delete enemy;
    for (tile* t: m_tiles) delete t;
    for (Spikes* spike : m_spikes) delete spike;
    for(Chopper* chopper: m_choppers) delete chopper;
    delete m_player;
    delete transition;
}
void GameWindow::stopGame(){

}
void GameWindow::initializeGame() {
    m_gameTimer.stop();
    for (Enemy* enemy : m_enemies) disconnect(enemy);

    for (Gate* gate : m_gates) delete gate;
    m_gates.clear();

    for (Enemy* enemy : m_enemies) {
        delete enemy;
    }
    m_enemies.clear();
    for (Spikes* spike : m_spikes) delete spike;
    m_spikes.clear();
    for(Chopper* chopper: m_choppers) delete chopper;
    m_choppers.clear();
    delete transition;
    transition = new Transition(transitionX,transitionY,transitionWidth,transitionHeight);
    createTilesandWallsandCeiling();
    m_player = new player(true, total_health, this);
    if(PositionPlayerx==-1){
    if (!m_tiles.isEmpty()) {
        tile* firstTile = m_tiles.first();
        PositionPlayerx = firstTile->boundingRect().left();
        PositionPlayery = firstTile->boundingRect().y() - m_player->boundingRect().height();
    }
    }
    m_player->setPos(PositionPlayerx, PositionPlayery);
    m_player->setGround(PositionPlayery);
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
    if(Background){
        *Background = Background->scaled(640,480);
    painter.drawPixmap(0,0,*Background);
    }
    // Draw tiles
    for (tile* t : m_tiles) {
        if(dynamic_cast<PressureTile*>(t)){
            PressureTile* p = dynamic_cast<PressureTile*>(t);
            p->draw(&painter);
            //painter.drawRect(p->boundingRect());
        }else{
            if(false){
        painter.save();
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(t->boundingRect());
        painter.restore();
            }
        }
    }
    if(false){
    painter.setPen(QPen(Qt::green, 10));
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(transition->boundingRect());
    }
    // Draw Spikes
    for (Spikes* spike : m_spikes) {
        spike->render(&painter);
    }
    for(Chopper* chopper: m_choppers){
        chopper->render(&painter);
    }

    // Draw Enemies
    for (Enemy* enemy : m_enemies) {
        enemy->render(&painter);
    }

    // Draw gates
    for (Gate* gate : m_gates) {
        if(dynamic_cast<Exit*>(gate)){
            Exit* exit = dynamic_cast<Exit*>(gate);
            painter.drawPixmap(exit->pos().x(),exit->pos().y()-50, exit->pixmap());
        }else{
            painter.drawPixmap(gate->pos().x(),gate->pos().y()-50, gate->pixmap());

        }
        if (m_debugMode) {
            painter.setPen(QPen(Qt::red, 2));
            painter.drawRect(gate->boundingRect().translated(gate->pos()));
        }
    }

    // Draw player
    m_player->draw(&painter);

    if(Foreground){
        *Foreground = Foreground->scaled(640,480);
        painter.drawPixmap(0,0,*Foreground);
    }
    if(false){
    for (wall* w : m_walls) {
        painter.drawRect(w->boundingRect());
        if (m_debugMode) {
            painter.setPen(QPen(Qt::green, 2));
            painter.setBrush(Qt::transparent);
            painter.drawRect(w->boundingRect().translated(w->pos()));
        }
    }

    for (ceiling* c : m_ceilings) {
        painter.drawRect(c->boundingRect());
        if (m_debugMode) {
            painter.setPen(QPen(Qt::green, 2));
            painter.setBrush(Qt::transparent);
            painter.drawRect(c->boundingRect().translated(c->pos()));
        }
    }
    }
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

            // Stop all timers
            m_gameTimer.stop();

            // Disconnect all signals from enemies
            for (Enemy* enemy : m_enemies) {
                disconnect(enemy);
            }

            // Initialize game
            initializeGame();

            // Start timer after initialization
            m_gameTimer.start();

            // Resize workaround
            QSize orig = size();
            resize(orig.width(), orig.height() + 1);
            resize(orig);

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

    createTilesandWallsandCeiling();

    if(PositionPlayerx==-1){
        if (!m_tiles.isEmpty()) {
            tile* firstTile = m_tiles.first();
            PositionPlayerx = firstTile->boundingRect().left();
            PositionPlayery = firstTile->boundingRect().y() - m_player->boundingRect().height();
        }
    }
    m_player->setPos(PositionPlayerx, PositionPlayery);
    m_player->setGround(PositionPlayery);

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
    total_health = m_player->healthBar()->getHealth();
    // Check if player is out of bounds
    if (m_player->pos().y() > height() ||
        m_player->pos().x() < -50 ||
        m_player->pos().x() > width() + 50) {
        m_gameOver = true;
        m_gameTimer.stop();
        update();
        return;
    }

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

    m_player->update(m_tiles,m_gates,m_choppers,m_walls,m_ceilings);
    QRectF playerBox = m_player->boundingRect().translated(m_player->pos());
    QRectF transitionBox = transition->boundingRect();
    if(transitionBox.intersects(playerBox)){
        // Stop timers before transitioning
        m_gameTimer.stop();

        // Call getNextRoom which will handle the transition
        getNextRoom();

        // Only initialize if we're not transitioning to a new level
        if (isVisible()) {
            initializeGame();
            m_gameTimer.start();

            // Resize workaround
            QSize orig = size();
            resize(orig.width(), orig.height() + 1);
            resize(orig);

            update();
        }
    }

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
                                      int tileWidth, int tileHeight, bool createEnemy,
                                      int overlap, const QList<int>& spikeIndices,
                                      const QList<int>& pressureIndices,
                                      const QList<int>& gateIndices,  const QList<int>& choppersIndices) {
    QList<tile*> tileList;

    for (int i = 0; i < count; i++) {
        bool tileHasEnemy = createEnemy && (i == 0);
        int x = startX + i * (tileWidth - overlap);

        tile* newTile = nullptr;
        if (pressureIndices.contains(i)) {
            newTile = new PressureTile(x, y, tileHasEnemy,tileWidth,tileHeight);
        } else {
            newTile = new tile(x, y, tileHasEnemy,tileWidth, tileHeight);
        }
        tileList.append(newTile);
        if (choppersIndices.contains(i)) {
            Chopper* chopper = new Chopper(QPointF(x, y - 80 + 20),15,200,0,1000);
            m_choppers.append(chopper);
            chopper->setPos(x, y - 80 + 20);
        }
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
    transition = new Transition(transitionX,transitionY,transitionWidth,transitionHeight);
    transition->setPos(transitionX,transitionY);
    return tileList;
}

QList<ceiling*> GameWindow::createCeiling(int startX, int y,
                                      int tileWidth, int tileHeight) {
    QList<ceiling*> ceilingsList;

    ceiling* Ceiling = new ceiling(startX,y,tileWidth,tileHeight);

    ceilingsList.append(Ceiling);

    return ceilingsList;
}
void GameWindow::addExit(int x, int y){
    m_gates.append(new Exit(x,y));
}
QList<wall*> GameWindow::createWalls(int startX, int y,
                                      int tileWidth, int tileHeight, bool right) {
    QList<wall*> wallsList;

    wall* Wall = new wall(startX,y,tileWidth,tileHeight,right);

    wallsList.append(Wall);

    return wallsList;
}

void GameWindow::createTilesandWallsandCeiling() {

}



void GameWindow::connectPressureTileToGate(int pressureTileIndex, int gateIndex) {
    if (pressureTileIndex >= 0 && pressureTileIndex < m_tiles.size() &&
        gateIndex >= 0 && gateIndex < m_gates.size()) {
        PressureTile* pt = dynamic_cast<PressureTile*>(m_tiles[pressureTileIndex]);
        if (pt && m_gates[gateIndex]) {
            pt->connectToGate(m_gates[gateIndex]);
        }
    }
}
