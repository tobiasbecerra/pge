#include "reserva.h"
#include <iostream>

Reserva::Reserva(const Pasajero& pasajero, Vuelo* vuelo, int asiento)
    : pasajero(pasajero), vuelo(vuelo), asiento(asiento){
    vuelo->ocuparAsiento(asiento);
}

void Reserva::mostrarDetalle() const{
    cout << "Reserva confirmada para " << pasajero.getNombre();
    cout << " (DNI: " << pasajero.getDNI() << ")\n";
    cout << "Vuelo: " << vuelo->getCodigo() << " a " << vuelo->getDestino();
    cout << " | Asiento: " << asiento << "\n";
}
