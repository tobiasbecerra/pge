#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>

class Empleado {
protected:
    std::string nombre;
    int id;
    float salarioBase;

public:
    Empleado(std::string nombre, int id, float salarioBase);
    virtual ~Empleado() = default;

    virtual float calcularSalario() const = 0; // Método abstracto
    virtual void mostrarInformacion() const = 0;
};

#endif
