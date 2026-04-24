#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QVector>
#include <QMouseEvent>

class HomeScreen : public QWidget {
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);


signals:
    void startGame(QVector<QPixmap> selectedBirdFrames, bool soundEnabled);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPixmap background, title, playButton;
    QVector<QVector<QPixmap>> birdAnimations;
    QPixmap leftArrow, rightArrow;
    QPixmap soundOnIcon, soundOffIcon;
    int currentBirdIndex;

    QRect playRect, leftArrowRect, rightArrowRect, soundButtonRect;

    bool soundEnabled;

    void updateRects();
};

#endif // HOMESCREEN_H
