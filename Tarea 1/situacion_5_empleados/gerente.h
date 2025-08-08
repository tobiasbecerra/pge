#ifndef GERENTE_H
#define GERENTE_H

#include "empleado.h"

class Gerente : public Empleado {
private:
    float bonoGerencia;

public:
    Gerente(std::string nombre, int id, float salarioBase, float bono);
    float calcularSalario() const override;
    void mostrarInformacion() const override;
};

#endif
