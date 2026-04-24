#include <QApplication>
#include "homescreen.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    HomeScreen home;
    MainWindow *game = nullptr;

    home.show();

    // 👇 UPDATED to accept QVector<QPixmap>
    QObject::connect(&home, &HomeScreen::startGame, [&home, &game](QVector<QPixmap> selectedBirdFrames, bool soundEnabled) {
        home.hide();

        game = new MainWindow(nullptr, selectedBirdFrames, soundEnabled);
        game->show();

        QObject::connect(game, &MainWindow::exitToHome, [&home, &game]() {
            game->hide();
            home.show();
            game->deleteLater();
            game = nullptr;
        });
    });

    return app.exec();
}
