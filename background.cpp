#include "background.h"

Background::Background(const QString &path)
    : image(path) {}

void Background::draw(QPainter &painter, int width, int height) {
    painter.drawPixmap(0, 0, width, height, image);
}
