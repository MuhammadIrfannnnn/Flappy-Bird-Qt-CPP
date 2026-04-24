#include "bird.h"

Bird::Bird(const QVector<QPixmap> &frames, const QPoint &startPos)
    : frames(frames), currentFrame(0), frameCounter(0),
    rect(startPos.x(), startPos.y(), 34, 24), velocity(0) {}

void Bird::update() {
    rect.moveTop(rect.top() + velocity);
    velocity += 1;

    frameCounter++;
    if (frameCounter % 15 == 0) {
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void Bird::jump() {
    velocity = -10;
}

QRect Bird::getRect() const {
    return rect;
}

void Bird::reset() {
    rect.moveTo(100, 250);
    velocity = 0;
    currentFrame = 0;
    frameCounter = 0;
}

QPixmap Bird::getCurrentFrame() const {
    return frames[currentFrame];
}
