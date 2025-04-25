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
    m_enemy = new Enemy(this);
    if (!m_enemy->initialize(":/sprites/enemy_sprite.png", 64, 64)) {
        qWarning() << "Failed to initialize enemy!";
    }

    m_enemy->setPosition(QPoint(width() / 2 - 32, height() / 2 - 32));

    connect(m_enemy, &Enemy::positionChanged, this, [this]() { update(); });
    connect(m_enemy, &Enemy::visualChanged, this, [this]() { update(); });
    connect(m_enemy, &Enemy::died, this, [this]() {
        qDebug() << "Enemy has died!";

        // Handling the enemy death (respawn after delay, etc.)
        QTimer::singleShot(3000, this, [this]() {
            m_enemy->setPosition(QPoint(width() / 2 - 32, height() / 2 - 32));
            m_enemy->m_alive = true;
            m_enemy->setState(Enemy::WALKRIGHT);
        });
    });

    m_gameTimer.setInterval(16);
    connect(&m_gameTimer, &QTimer::timeout, this, &GameWindow::updateGame);
    m_gameTimer.start();
}

void GameWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    m_enemy->render(&painter);
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
        centerEnemyVertically();
        m_enemy->setPosition(QPoint(width() / 2 - 32, m_enemy->position().y()));
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
    centerEnemyVertically();
    QMainWindow::resizeEvent(event);
}

void GameWindow::centerEnemyVertically() {
    QPoint pos = m_enemy->position();
    pos.setY(height() / 2 - 32);
    m_enemy->setPosition(pos);
}

void GameWindow::drawDebugInfo(QPainter *painter) {
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    QStringList debugInfo;
    debugInfo << QString("FPS: %1").arg(m_fps)
              << QString("State: %1").arg(stateToString(m_enemy->m_currentState))
              << QString("Position: (%1, %2)").arg(m_enemy->position().x()).arg(m_enemy->position().y())
              << QString("Size: 64x64")
              << "D: Walk right | A: Walk Left"
              << "R: Attack right | L: Attack Left"
              << "K: Die Right | J: Die Left"
              << "+/-: Adjust speed | T: toggle debug";

    QRect infoBox(10, 10, 250, 20 * debugInfo.size() + 10);
    painter->fillRect(infoBox, QColor(255, 255, 255, 200));
    painter->drawRect(infoBox);

    for (int i = 0; i < debugInfo.size(); i++)
        painter->drawText(20, 30 + i * 20, debugInfo[i]);
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
    if (m_enemy) {
        m_enemy->update(width());
    }
}
