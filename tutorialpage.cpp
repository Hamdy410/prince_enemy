#include "tutorialpage.h"
#include <QPainter>
#include <QFont>

TutorialPage::TutorialPage(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Game Tutorial");
    setFixedSize(800, 600);

    // Create back button
    m_backButton = new QPushButton("Back to Menu", this);
    m_backButton->setFixedSize(150, 40);
    m_backButton->move(width() - 170, height() - 60);
    m_backButton->setStyleSheet("font-size: 14px; background-color: #333; color: white; border: 2px solid #555;");

    connect(m_backButton, &QPushButton::clicked, this, &TutorialPage::backToMenuRequested);

    // Prepare tutorial instructions
    m_instructions << "Controls:"
                   << "→ Right Arrow: Move right"
                   << "← Left Arrow: Move left"
                   << "↑ Up Arrow: Jump"
                   << "↓ Down Arrow: Crouch"
                   << "Space: Hop"
                   << "Z: Attack"
                   << ""
                   << "Game Tips:"
                   << "- Watch your health bar"
                   << "- Avoid falling from great heights"
                   << "- Use pressure tiles to activate gates"
                   << "- Time your jumps carefully";
}

TutorialPage::~TutorialPage()
{
}

void TutorialPage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw background
    drawBrickPattern(&painter);

    // Draw semi-transparent overlay
    painter.fillRect(rect(), QColor(0, 0, 0, 150));

    // Draw title
    QFont titleFont("Arial", 36, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(Qt::white);
    painter.drawText(rect().adjusted(0, 30, 0, 0), Qt::AlignHCenter | Qt::AlignTop, "Game Tutorial");

    // Draw instructions
    QFont instructionFont("Arial", 16);
    painter.setFont(instructionFont);

    int yPos = 120;
    for (const QString& instruction : m_instructions) {
        if (instruction.isEmpty()) {
            yPos += 20; // Add space between sections
            continue;
        }

        if (instruction.startsWith("Controls:") || instruction.startsWith("Game Tips:")) {
            // Section headers
            QFont sectionFont("Arial", 20, QFont::Bold);
            painter.setFont(sectionFont);
            painter.drawText(100, yPos, instruction);
            painter.setFont(instructionFont);
            yPos += 40;
        } else {
            // Regular instructions
            painter.drawText(120, yPos, instruction);
            yPos += 30;
        }
    }
}

void TutorialPage::drawBrickPattern(QPainter* painter)
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
