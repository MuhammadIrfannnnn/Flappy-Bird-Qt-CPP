#ifndef PILLAR_H
#define PILLAR_H

#include <QRect>
#include <QVector>

class Pillar {
public:
    static QVector<QRect> generateInitial(int count, int screenHeight);
    static void movePipes(QVector<QRect> &pipes, int screenWidth, int screenHeight);
    static bool checkCollision(const QRect &bird, const QVector<QRect> &pipes);
};

#endif
