#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class Jugador : public QGraphicsRectItem {
public:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
