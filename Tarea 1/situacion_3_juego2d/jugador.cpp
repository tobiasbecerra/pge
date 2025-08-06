#include "jugador.h"

void Jugador::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left && x() > 0)
        setPos(x() - 10, y());
    else if (event->key() == Qt::Key_Right && x() + rect().width() < 800)
        setPos(x() + 10, y());
    else if (event->key() == Qt::Key_Up && y() > 0)
        setPos(x(), y() - 10);
    else if (event->key() == Qt::Key_Down && y() + rect().height() < 600)
        setPos(x(), y() + 10);
}
