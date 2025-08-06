// === item.cpp ===
#include "item.h"

Item::Item(const QString &imagePath) {
    setPixmap(QPixmap(imagePath).scaled(30, 30));
}
