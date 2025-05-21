#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H

#include <QWidget>
#include <QPushButton>

class TutorialPage : public QWidget
{
    Q_OBJECT

public:
    explicit TutorialPage(QWidget* parent = nullptr);
    ~TutorialPage();

protected:
    void paintEvent(QPaintEvent* event) override;
    void drawBrickPattern(QPainter* painter);

signals:
    void backToMenuRequested();

private:
    QPushButton* m_backButton;
    QStringList m_instructions;
};

#endif // TUTORIALPAGE_H
