#include "pillar.h"
#include <QRandomGenerator>

QVector<QRect> Pillar::generateInitial(int count, int screenHeight) {
    QVector<QRect> pipes;
    int gapHeight = 200;
    int pipeWidth = 50;
    int spacing = 300;

    for (int i = 0; i < count; ++i) {
        int gapY = QRandomGenerator::global()->bounded(100, screenHeight - gapHeight - 100);
        int xPos = 500 + i * spacing;

        pipes.append(QRect(xPos, 0, pipeWidth, gapY));
        pipes.append(QRect(xPos, gapY + gapHeight, pipeWidth, screenHeight - (gapY + gapHeight)));
    }

    return pipes;
}

void Pillar::movePipes(QVector<QRect> &pipes, int screenWidth, int screenHeight) {
    int gapHeight = 200;
    int pipeWidth = 50;
    int spacing = 300;

    for (int i = 0; i < pipes.size(); ++i) {
        pipes[i].translate(-3, 0);
    }
    if (!pipes.isEmpty() && pipes.first().right() < 0) {
        pipes.removeFirst();
        pipes.removeFirst();

        int gapY = QRandomGenerator::global()->bounded(100, screenHeight - gapHeight - 100);
        int lastX = pipes[pipes.size() - 2].x();
        int newX = lastX + spacing;

        pipes.append(QRect(newX, 0, pipeWidth, gapY));
        pipes.append(QRect(newX, gapY + gapHeight, pipeWidth, screenHeight - (gapY + gapHeight)));
    }
}

bool Pillar::checkCollision(const QRect &bird, const QVector<QRect> &pipes) {
    for (const QRect &pipe : pipes) {
        if (bird.intersects(pipe))
            return true;
    }
    return false;
}
