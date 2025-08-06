#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "jugador.h"

class Game : public QGraphicsView {
public:
    Game(QWidget *parent = nullptr);

private:
    QGraphicsScene *scene;
    Jugador *jugador;
};

#endif
