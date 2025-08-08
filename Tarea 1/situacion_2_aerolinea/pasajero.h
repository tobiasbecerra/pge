#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
using namespace std;

class Pasajero
{

private:

    string nombre;
    string dni;

public:

    Pasajero(const string& nombre, const string& dni);
    string getNombre() const;
    string getDNI() const;

};

#endif // PASAJERO_H
