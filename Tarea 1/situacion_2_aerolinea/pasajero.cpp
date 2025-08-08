#include "pasajero.h"

Pasajero::Pasajero(const string& nombre, const string& dni) : nombre(nombre), dni(dni){}

string Pasajero::getNombre() const{
    return nombre;
}

string Pasajero::getDNI() const{
    return dni;
}
