#include "pasajero.h"
#include "vuelo.h"
#include "reserva.h"
#include <iostream>
using namespace std;

int main(){

    Vuelo vuelo1("AR123", "Cordoba", 100);
    Pasajero p1("Laura Gomez", "12345678");

    int asiento = 10;
    if(vuelo1.estaDisponible(asiento)){
        Reserva r1(p1, &vuelo1, asiento);
        r1.mostrarDetalle();
    }else{
        cout << "El asiento no esta disponible";
    }

    return 0;

}
