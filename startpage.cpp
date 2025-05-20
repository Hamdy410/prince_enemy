// startpage.cpp
#include "startpage.h"
#include <QPainter>
#include <QFont>
#include <QKeyEvent>
#include <QMouseEvent>

StartPage::StartPage(const QString& gameTitle, int levelNumber, QWidget* parent)
    : QWidget(parent), m_gameTitle(gameTitle), m_levelNumber(levelNumber)
{
    setWindowTitle(gameTitle);
    setFixedSize(800, 600); // Or whatever your game window size is
}

void StartPage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw the same background as your game window
    drawBrickPattern(&painter);

    // Draw semi-transparent overlay for text readability (optional)
    painter.fillRect(rect(), QColor(0, 0, 0, 120));

    // Draw Title
    QFont titleFont("Arial", 48, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, m_gameTitle);

    // Draw Level Number
    QFont levelFont("Arial", 24, QFont::Normal);
    painter.setFont(levelFont);
    QString levelText = QString("Level %1").arg(m_levelNumber);
    QRect levelRect = rect().adjusted(0, 80, 0, 0); // 80 px down from top
    painter.drawText(levelRect, Qt::AlignHCenter | Qt::AlignTop, levelText);

    // Draw Message
    QFont msgFont("Arial", 18, QFont::Normal);
    painter.setFont(msgFont);
    QString msgText = "Press any key or click to start!";
    QRect msgRect = rect().adjusted(0, 160, 0, 0); // further down
    painter.drawText(msgRect, Qt::AlignHCenter | Qt::AlignTop, msgText);
}

void StartPage::keyPressEvent(QKeyEvent*)
{
    emit startRequested();
}

void StartPage::mousePressEvent(QMouseEvent*)
{
    emit startRequested();
}

// Copy your drawBrickPattern implementation from GameWindow here
void StartPage::drawBrickPattern(QPainter* painter)
{
    int brickWidth = 60, brickHeight = 30;
    QColor brickColor(0, 0, 0);
    QColor mortarColor(220, 220, 220);

    for (int y = 0; y < height(); y += brickHeight) {
        for (int x = (y / brickHeight) % 2 == 0 ? 0 : -brickWidth / 2; x < width(); x += brickWidth) {
            QRect brickRect(x, y, brickWidth, brickHeight);
            painter->fillRect(brickRect, brickColor);
            painter->setPen(mortarColor);
            painter->drawRect(brickRect);
        }
    }
}
