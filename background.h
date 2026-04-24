#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPixmap>
#include <QPainter>

class Background {
private:
    QPixmap image;

public:
    Background(const QString &path);
    void draw(QPainter &painter, int width, int height);
};

#endif

