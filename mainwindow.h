#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QSoundEffect>
#include "bird.h"
#include "pillar.h"
#include "background.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, QVector<QPixmap> birdFrames = {}, bool soundEnabled = true);
    void setSoundEnabled(bool enabled) { soundEnabled = enabled; }
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void gameLoop();

private:
    Background background;
    Bird bird;
    QVector<QRect> pipes;
    QPixmap pipeImage;

    QPixmap gameOverBanner, medalBronze, medalSilver, medalGold, medalPlatinum;
    QPixmap restartBtn, exitBtn;
    QVector<QPixmap> numberImages;

    QRect restartRect, exitRect;

    int score, bestScore;
    bool gameOver;
    QTimer timer;

    QSoundEffect wingSound;
    QSoundEffect hitSound;
    QSoundEffect pointSound;

    bool soundEnabled;

    void resetGame();
    void drawUI(QPainter &painter);

signals:
    void exitToHome();
};

#endif // MAINWINDOW_H
