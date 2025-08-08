#ifndef RESERVA_H
#define RESERVA_H

#include "pasajero.h"
#include "vuelo.h"

class Reserva{

private:

    Pasajero pasajero;
    Vuelo* vuelo;
    int asiento;

public:

    Reserva(const Pasajero& pasajero, Vuelo* vuelo, int asiento);
    void mostrarDetalle() const;

};

#endif // RESERVA_H
