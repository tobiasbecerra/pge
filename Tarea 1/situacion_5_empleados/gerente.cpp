#include "gerente.h"
#include <iostream>

Gerente::Gerente(std::string nombre, int id, float salarioBase, float bono)
    : Empleado(nombre, id, salarioBase), bonoGerencia(bono) {}

float Gerente::calcularSalario() const {
    return salarioBase + bonoGerencia;
}

void Gerente::mostrarInformacion() const {
    std::cout << "Gerente: " << nombre << " (ID: " << id << ")\n";
    std::cout << "Salario total: $" << calcularSalario() << "\n";
}
