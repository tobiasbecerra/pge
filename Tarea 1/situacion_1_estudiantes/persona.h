#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
using namespace std;

class Persona{
protected:
    string nombre;
    string dni;

public:
    Persona(const string& nombre, const string& dni);
    string getNombre() const;
    string getDNI() const;

    void setNombre(const string& nuevoNombre);
    void setDNI(const string& nuevoDNI);
};

#endif // PERSONA_H
