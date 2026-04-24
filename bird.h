#ifndef BIRD_H
#define BIRD_H

#include <QPixmap>
#include <QRect>
#include <QVector>

class Bird {
public:
    Bird(const QVector<QPixmap> &frames, const QPoint &startPos = QPoint(100, 250));
    void update();
    void jump();
    QRect getRect() const;
    void reset();
    QPixmap getCurrentFrame() const;

private:
    QVector<QPixmap> frames;
    int currentFrame;
    int frameCounter;

    QRect rect;
    int velocity;

};

#endif
