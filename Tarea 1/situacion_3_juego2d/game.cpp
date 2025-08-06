#include "game.h"
#include "enemigo.h"
#include "item.h"

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    setFixedSize(800, 600);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);
    setScene(scene);

    jugador = new Jugador();
    jugador->setRect(0, 0, 40, 40);
    jugador->setBrush(Qt::blue);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();

    scene->addItem(jugador);
    jugador->setPos(400, 500);

    // Agregar enemigos
    for (int i = 0; i < 3; i++) {
        Enemigo *enemigo = new Enemigo();
        enemigo->setPos(100 + i * 200, 0);
        scene->addItem(enemigo);
    }

    // Agregar item
    Item *pocion = new Item(":/pocion.png");
    pocion->setPos(300, 300);
    scene->addItem(pocion);
}
