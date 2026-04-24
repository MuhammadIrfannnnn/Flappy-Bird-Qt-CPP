#include "homescreen.h"
#include <QPainter>

HomeScreen::HomeScreen(QWidget *parent)
    : QWidget(parent), currentBirdIndex(0), soundEnabled(true) {
    setFixedSize(500, 700);

    background = QPixmap(":/images/background.png");
    title = QPixmap(":/images/logo.png");
    playButton = QPixmap(":/images/play.png");
    leftArrow = QPixmap(":/images/left.png");
    rightArrow = QPixmap(":/images/right.png");
    soundOnIcon = QPixmap(":/images/soundEnabled.png");
    soundOffIcon = QPixmap(":/images/soundDisabled.png");

    birdAnimations.append({
        QPixmap(":/images/bird_yellow_up.png"),
        QPixmap(":/images/bird_yellow_middle.png"),
        QPixmap(":/images/bird_yellow_down.png")
    });

    birdAnimations.append({
        QPixmap(":/images/bird_red_up.png"),
        QPixmap(":/images/bird_red_middle.png"),
        QPixmap(":/images/bird_red_down.png")
    });

    birdAnimations.append({
        QPixmap(":/images/bird_blue_up.png"),
        QPixmap(":/images/bird_blue_middle.png"),
        QPixmap(":/images/bird_blue_down.png")
    });

    updateRects();
}

void HomeScreen::updateRects() {
    playRect = QRect(width() / 2 - 50, 500, 100, 50);
    leftArrowRect = QRect(width() / 2 - 100, 300, 40, 40);
    rightArrowRect = QRect(width() / 2 + 60, 300, 40, 40);
    soundButtonRect = QRect(width() - 60, 20, 40, 40);
}

void HomeScreen::paintEvent(QPaintEvent *) {
    static int frame = 0;
    static int frameCounter = 0;

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
    painter.drawPixmap(width() / 2 - title.width() / 2, 100, title);
    painter.drawPixmap(playRect, playButton);
    painter.drawPixmap(leftArrowRect, leftArrow);
    painter.drawPixmap(rightArrowRect, rightArrow);

    frameCounter++;
    if (frameCounter % 200 == 0) {
        frame = (frame + 1) % birdAnimations[currentBirdIndex].size();
    }

    painter.drawPixmap(width() / 2 - 20, 290, 40, 40, birdAnimations[currentBirdIndex][frame]);

    if (soundEnabled)
        painter.drawPixmap(soundButtonRect, soundOnIcon);
    else
        painter.drawPixmap(soundButtonRect, soundOffIcon);

    update();
}

void HomeScreen::mousePressEvent(QMouseEvent *event) {
    QPoint pos = event->pos();

    if (leftArrowRect.contains(pos)) {
        currentBirdIndex = (currentBirdIndex - 1 + birdAnimations.size()) % birdAnimations.size();
    } else if (rightArrowRect.contains(pos)) {
        currentBirdIndex = (currentBirdIndex + 1) % birdAnimations.size();
    } else if (playRect.contains(pos)) {
        emit startGame(birdAnimations[currentBirdIndex], soundEnabled);
    } else if (soundButtonRect.contains(pos)) {
        soundEnabled = !soundEnabled;
    }

    update();
}
