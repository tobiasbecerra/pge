#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QString>

class Producto{

private:
    QString nombre;
    int cantidad;
    float precio;

public:

    Producto(QString nombre, int cantidad, float precio);
    QString getNombre() const;
    int getCantidad() const;
    float getPrecio() const;

    void setCantidad(int nuevaCantidad);
    void setPrecio(float nuevoPrecio);

};

#endif // PRODUCTO_H
