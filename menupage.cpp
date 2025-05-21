#include "menupage.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QFont>

MenuPage::MenuPage(const QString& gameTitle, QWidget* parent)
    : QWidget(parent), m_gameTitle(gameTitle)
{
    setWindowTitle(gameTitle);
    setFixedSize(800, 600);

    // Create buttons
    m_playButton = new QPushButton("Play Game", this);
    m_playButton->setFixedSize(200, 50);
    m_playButton->setStyleSheet("font-size: 18px; background-color: #333; color: white; border: 2px solid #555;");

    m_tutorialButton = new QPushButton("Tutorial", this);
    m_tutorialButton->setFixedSize(200, 50);
    m_tutorialButton->setStyleSheet("font-size: 18px; background-color: #333; color: white; border: 2px solid #555;");

    // Position buttons
    m_playButton->move(width()/2 - m_playButton->width()/2, height()/2);
    m_tutorialButton->move(width()/2 - m_tutorialButton->width()/2, height()/2 + 70);

    // Connect signals
    connect(m_playButton, &QPushButton::clicked, this, &MenuPage::playGameRequested);
    connect(m_tutorialButton, &QPushButton::clicked, this, &MenuPage::tutorialRequested);
}

MenuPage::~MenuPage()
{
}

void MenuPage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw background
    drawBrickPattern(&painter);

    // Draw semi-transparent overlay
    painter.fillRect(rect(), QColor(0, 0, 0, 120));

    // Draw title
    QFont titleFont("Arial", 48, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(rect().adjusted(0, 50, 0, 0), Qt::AlignHCenter | Qt::AlignTop, m_gameTitle);
}

void MenuPage::drawBrickPattern(QPainter* painter)
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
