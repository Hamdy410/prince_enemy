#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(const QString& gameTitle, QWidget* parent = nullptr);
    ~MenuPage();

protected:
    void paintEvent(QPaintEvent* event) override;
    void drawBrickPattern(QPainter* painter);

signals:
    void playGameRequested();
    void tutorialRequested();

private:
    QString m_gameTitle;
    QPushButton* m_playButton;
    QPushButton* m_tutorialButton;
};

#endif // MENUPAGE_H
