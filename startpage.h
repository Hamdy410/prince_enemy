// startpage.h
#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

class StartPage : public QWidget
{
    Q_OBJECT
public:
    explicit StartPage(const QString& gameTitle, int levelNumber, QWidget* parent = nullptr);

signals:
    void startRequested();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QString m_gameTitle;
    int m_levelNumber;

    void drawBrickPattern(QPainter* painter);
};

#endif // STARTPAGE_H
