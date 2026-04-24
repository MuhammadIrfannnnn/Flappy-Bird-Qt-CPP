#include "mainwindow.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent, QVector<QPixmap> birdFrames, bool soundEnabled)
    : QMainWindow(parent),
    background(":/images/background.png"),
    bird(birdFrames),
    pipeImage(":/images/pipe.png"),
    score(0),
    bestScore(0),
    gameOver(false),
    soundEnabled(soundEnabled)
{
    QFile file("best_score.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> bestScore;
        file.close();
    }

    setFixedSize(500, 700);

    gameOverBanner = QPixmap(":/images/gameOver.png");
    restartBtn = QPixmap(":/images/restart.png");
    exitBtn = QPixmap(":/images/exit.png");

    medalBronze = QPixmap(":/images/scoreBoard_bronze.png");
    medalSilver = QPixmap(":/images/scoreBoard_silver.png");
    medalGold = QPixmap(":/images/scoreBoard_gold.png");
    medalPlatinum = QPixmap(":/images/scoreBoard_platinum.png");

    for (int i = 0; i <= 9; ++i) {
        QPixmap pix(QString("C:/Users/C2D/Desktop/hello/images/0-9/%1.png").arg(i));
        numberImages.append(pix);
    }

    restartRect = QRect(width() / 2 - 80, 400, 50, 50);
    exitRect = QRect(width() / 2 + 30, 400, 50, 50);

    wingSound.setSource(QUrl("qrc:/sounds/assets_sound_wing.wav"));
    wingSound.setVolume(0.5f);

    hitSound.setSource(QUrl("qrc:/sounds/assets_sound_hit.wav"));
    hitSound.setVolume(0.5f);

    pointSound.setSource(QUrl("qrc:/sounds/assets_sound_point.wav"));
    pointSound.setVolume(0.5f);

    resetGame();

    connect(&timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer.start(16);
}

MainWindow::~MainWindow() {}

void MainWindow::resetGame() {
    pipes = Pillar::generateInitial(3, height());
    bird.reset();
    score = 0;
    gameOver = false;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    background.draw(painter, width(), height());

    for (const QRect &pipe : pipes)
        painter.drawPixmap(pipe, pipeImage);

    painter.drawPixmap(bird.getRect(), bird.getCurrentFrame());

    {
        QString scoreStr = QString::number(score);
        const int digitW = 20;
        const int digitH = 30;
        const int margin = 5;
        int totalWidth = scoreStr.length() * digitW;
        int scoreX = width() - totalWidth - margin;
        int scoreY = margin;
        for (QChar ch : scoreStr) {
            painter.drawPixmap(scoreX, scoreY, digitW, digitH, numberImages[ch.digitValue()]);
            scoreX += digitW;
        }
    }

    if (gameOver)
        drawUI(painter);
}

void MainWindow::drawUI(QPainter &painter) {
    painter.drawPixmap(width() / 2 - 100, 100, 200, 50, gameOverBanner);

    QPixmap medalToShow = medalBronze;
    if (score >= 100) medalToShow = medalPlatinum;
    else if (score >= 50) medalToShow = medalGold;
    else if (score >= 10) medalToShow = medalSilver;

    QRect medalRect(width() / 2 - 150, 180, 300, 120);
    painter.drawPixmap(medalRect, medalToShow);

    QString scoreStr = QString::number(score);
    int digitW = 20, digitH = 30;
    int scoreX = medalRect.center().x() - (scoreStr.length() * digitW) / 2;
    int scoreY = medalRect.top() + 30;

    for (QChar ch : scoreStr)
        painter.drawPixmap(scoreX += digitW, scoreY, digitW, digitH, numberImages[ch.digitValue()]);

    QString bestStr = QString::number(bestScore);
    int bestX = medalRect.center().x() - (bestStr.length() * digitW) / 2;
    int bestY = scoreY + 40;

    for (QChar ch : bestStr)
        painter.drawPixmap(bestX += digitW, bestY, digitW, digitH, numberImages[ch.digitValue()]);

    painter.drawPixmap(restartRect, restartBtn);
    painter.drawPixmap(exitRect, exitBtn);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && !gameOver) {
        bird.jump();
        if (soundEnabled) {
            wingSound.play();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (!gameOver)
        return;

    if (restartRect.contains(event->pos())) {
        resetGame();
    } else if (exitRect.contains(event->pos())) {
        emit exitToHome();
    }
}

void MainWindow::gameLoop() {
    if (gameOver) return;

    bird.update();
    Pillar::movePipes(pipes, width(), height());

    for (int i = 0; i < pipes.size(); i += 2) {
        QRect topPipe = pipes[i];

        if (!topPipe.isNull() && topPipe.right() < bird.getRect().left()) {
            score++;
            if (soundEnabled) {
                pointSound.play();
            }

            if (score > bestScore) {
                bestScore = score;
                QFile file("best_score.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(&file);
                    out << bestScore;
                    file.close();
                }
            }

            pipes[i] = QRect();
            pipes[i + 1] = QRect();
            break;
        }
    }

    if (Pillar::checkCollision(bird.getRect(), pipes) ||
        bird.getRect().top() < 0 || bird.getRect().bottom() > height()) {
        gameOver = true;
        if (soundEnabled) {
            hitSound.play();
        }
    }

    update();
}
