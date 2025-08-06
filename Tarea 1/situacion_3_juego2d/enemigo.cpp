// === enemigo.cpp ===
#include "enemigo.h"
#include <QGraphicsScene>
#include <stdlib.h>

Enemigo::Enemigo() {
    setRect(0, 0, 40, 40);
    setBrush(Qt::red);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
    timer->start(100);
}

void Enemigo::mover() {
    setPos(x(), y() + 5);
    if (y() > 600) {
        setPos(rand() % 760, 0);
    }
}
