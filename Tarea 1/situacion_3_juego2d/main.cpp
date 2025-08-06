#include "game.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Game juego;
    juego.show();
    return a.exec();
}
