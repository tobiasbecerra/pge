#include "desarrollador.h"
#include <iostream>

Desarrollador::Desarrollador(std::string nombre, int id, float salarioBase, int proyectos)
    : Empleado(nombre, id, salarioBase), proyectos(proyectos) {}

float Desarrollador::calcularSalario() const {
    return salarioBase + (proyectos * 500); // Bonus por proyecto
}

void Desarrollador::mostrarInformacion() const {
    std::cout << "Desarrollador: " << nombre << " (ID: " << id << ")\n";
    std::cout << "Salario total: $" << calcularSalario() << "\n";
}
