#ifndef DESARROLLADOR_H
#define DESARROLLADOR_H

#include "empleado.h"

class Desarrollador : public Empleado {
private:
    int proyectos;

public:
    Desarrollador(std::string nombre, int id, float salarioBase, int proyectos);
    float calcularSalario() const override;
    void mostrarInformacion() const override;
};

#endif
