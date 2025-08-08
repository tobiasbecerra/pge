#include "producto.h"

Producto::Producto(QString nombre, int cantidad, float precio)
    : nombre(nombre), cantidad(cantidad), precio(precio) {}

QString Producto::getNombre() const {
    return nombre;
}

int Producto::getCantidad() const {
    return cantidad;
}

float Producto::getPrecio() const {
    return precio;
}

void Producto::setCantidad(int nuevaCantidad) {
    cantidad = nuevaCantidad;
}

void Producto::setPrecio(float nuevoPrecio) {
    precio = nuevoPrecio;
}
