#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "persona.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Estudiante : public Persona{
private:
    vector<pair<string, float >> materias;
public:
    Estudiante(const string& nombre, const string& dni);
    void agregarMateria(const string &materia, float nota);
    void mostrarResumenAcademico() const;
};

#endif // ESTUDIANTE_H
