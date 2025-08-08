#include "gerente.h"
#include "desarrollador.h"
#include <vector>
#include <memory>
#include <iostream>
int main() {
    std::vector<std::unique_ptr<Empleado>> empleados;

    empleados.push_back(std::make_unique<Gerente>("Laura", 1001, 5000, 2000));
    empleados.push_back(std::make_unique<Desarrollador>("Carlos", 1002, 3000, 3));

    for (const auto& emp : empleados) {
        emp->mostrarInformacion();
        std::cout << "----------------------\n";
    }

    return 0;
}
