#include "ventana.h"
#include "producto.h"
#include "inventario.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

Ventana::Ventana(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Gestión de Inventario");
    resize(600, 400);

    inputNombre = new QLineEdit();
    inputCantidad = new QLineEdit();
    inputPrecio = new QLineEdit();

    inputCantidad->setPlaceholderText("Cantidad (entero)");
    inputPrecio->setPlaceholderText("Precio (decimal)");

    btnAgregar = new QPushButton("Agregar");
    btnActualizar = new QPushButton("Actualizar");
    btnEliminar = new QPushButton("Eliminar");

    tabla = new QTableWidget();
    tabla->setColumnCount(3);
    tabla->setHorizontalHeaderLabels({"Nombre", "Cantidad", "Precio"});
    tabla->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QVBoxLayout *layout = new QVBoxLayout();

    QHBoxLayout *formLayout = new QHBoxLayout();
    formLayout->addWidget(inputNombre);
    formLayout->addWidget(inputCantidad);
    formLayout->addWidget(inputPrecio);
    layout->addLayout(formLayout);

    QHBoxLayout *botonesLayout = new QHBoxLayout();
    botonesLayout->addWidget(btnAgregar);
    botonesLayout->addWidget(btnActualizar);
    botonesLayout->addWidget(btnEliminar);
    layout->addLayout(botonesLayout);

    layout->addWidget(tabla);
    setLayout(layout);

    connect(btnAgregar, &QPushButton::clicked, this, &Ventana::agregarProducto);
    connect(btnActualizar, &QPushButton::clicked, this, &Ventana::actualizarProducto);
    connect(btnEliminar, &QPushButton::clicked, this, &Ventana::eliminarProducto);
    connect(tabla, &QTableWidget::cellClicked, this, &Ventana::seleccionarProducto);
}

void Ventana::refrescarTabla() {
    tabla->setRowCount(0);
    const QVector<Producto>& productos = inventario.obtenerProductos();
    for (int i = 0; i < productos.size(); ++i) {
        tabla->insertRow(i);
        tabla->setItem(i, 0, new QTableWidgetItem(productos[i].getNombre()));
        tabla->setItem(i, 1, new QTableWidgetItem(QString::number(productos[i].getCantidad())));
        tabla->setItem(i, 2, new QTableWidgetItem(QString::number(productos[i].getPrecio())));
    }
}

void Ventana::limpiarCampos() {
    inputNombre->clear();
    inputCantidad->clear();
    inputPrecio->clear();
    tabla->clearSelection();
}

void Ventana::agregarProducto() {
    QString nombre = inputNombre->text();
    int cantidad = inputCantidad->text().toInt();
    float precio = inputPrecio->text().toFloat();

    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre no puede estar vacío.");
        return;
    }

    inventario.agregar(Producto(nombre, cantidad, precio));
    refrescarTabla();
    limpiarCampos();
}

void Ventana::actualizarProducto() {
    int fila = tabla->currentRow();
    if (fila < 0) return;

    int cantidad = inputCantidad->text().toInt();
    float precio = inputPrecio->text().toFloat();

    inventario.actualizar(fila, cantidad, precio);
    refrescarTabla();
    limpiarCampos();
}

void Ventana::eliminarProducto() {
    int fila = tabla->currentRow();
    if (fila < 0) return;

    inventario.eliminar(fila);
    refrescarTabla();
    limpiarCampos();
}

void Ventana::seleccionarProducto(int fila, int) {
    inputNombre->setText(tabla->item(fila, 0)->text());
    inputCantidad->setText(tabla->item(fila, 1)->text());
    inputPrecio->setText(tabla->item(fila, 2)->text());
}
