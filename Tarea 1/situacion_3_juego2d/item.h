#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>

class Item : public QGraphicsPixmapItem {
public:
    Item(const QString &imagePath);
};

#endif
