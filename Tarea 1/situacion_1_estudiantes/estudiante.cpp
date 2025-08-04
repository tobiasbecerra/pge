#include "estudiante.h"

Estudiante::Estudiante(const string& nombre, const string& dni) : Persona(nombre, dni){}

void Estudiante::agregarMateria(const string &materia, float nota){
    materias.push_back(make_pair(materia, nota));
}

void Estudiante::mostrarResumenAcademico() const{
    cout << "Estudiante: " << nombre << " (DNI: " << dni << ")\n";
    cout << "Materias cursadas:\n";
    for(auto& m:materias){
        cout << " - " << m.first << ": " << m.second << "\n";
    }
}
