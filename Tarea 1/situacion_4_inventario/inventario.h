#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "producto.h"
#include <QVector>

class Inventario{

private:

    QVector<Producto> productos;

public:

    void agregar(const Producto& producto);
    void eliminar(int index);
    void actualizar(int index, int nuevaCantidad, float nuevoPrecio);
    const QVector<Producto>& obtenerProductos() const;

};

#endif // INVENTARIO_H
