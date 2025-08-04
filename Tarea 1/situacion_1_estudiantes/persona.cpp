#include "persona.h"

Persona::Persona(const string& nombre, const string& dni) : nombre(nombre), dni(dni){}

string Persona::getNombre()const{
    return nombre;
}

string Persona::getDNI()const{
    return dni;
}

void Persona::setNombre(const string &nuevoNombre){
    nombre = nuevoNombre;
}

void Persona::setDNI(const string &nuevoDNI){
    dni = nuevoDNI;
}
