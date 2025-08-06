#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsRectItem>
#include <QTimer>

class Enemigo : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    Enemigo();

public slots:
    void mover();
};

#endif // ENEMIGO_H
