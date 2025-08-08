#include "inventario.h"

void Inventario::agregar(const Producto& producto) {
    productos.append(producto);
}

void Inventario::eliminar(int index) {
    if (index >= 0 && index < productos.size())
        productos.removeAt(index);
}

void Inventario::actualizar(int index, int nuevaCantidad, float nuevoPrecio) {
    if (index >= 0 && index < productos.size()) {
        productos[index].setCantidad(nuevaCantidad);
        productos[index].setPrecio(nuevoPrecio);
    }
}

const QVector<Producto>& Inventario::obtenerProductos() const {
    return productos;
}
