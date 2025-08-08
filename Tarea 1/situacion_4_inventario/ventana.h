#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include "inventario.h"

class Ventana : public QWidget {
    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);

private slots:
    void agregarProducto();
    void actualizarProducto();
    void eliminarProducto();
    void seleccionarProducto(int fila, int columna);

private:
    QLineEdit *inputNombre;
    QLineEdit *inputCantidad;
    QLineEdit *inputPrecio;

    QPushButton *btnAgregar;
    QPushButton *btnActualizar;
    QPushButton *btnEliminar;

    QTableWidget *tabla;

    Inventario inventario;
    void refrescarTabla();
    void limpiarCampos();
};

#endif
