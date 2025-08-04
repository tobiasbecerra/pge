#include <iostream>
#include "estudiante.h"

int main() {

    Estudiante e1("Juan Pérez", "12345678");
    e1.agregarMateria("Matemática", 8.5);
    e1.agregarMateria("Programación", 9.0);
    e1.mostrarResumenAcademico();

    return 0;
}
