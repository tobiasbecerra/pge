#include "vuelo.h"

Vuelo::Vuelo(const string& codigo, const string& destino, int capacidad)
    : codigo(codigo), destino(destino), asientosTotales(capacidad), asientosDisponibles(capacidad, true){}

bool Vuelo::estaDisponible(int asiento) const{
    return asiento >= 0 && asiento < asientosTotales && asientosDisponibles[asiento];
}

void Vuelo::ocuparAsiento(int asiento){
    if(estaDisponible(asiento)){
        asientosDisponibles[asiento] = false;
    }
}

string Vuelo::getCodigo() const{
    return codigo;
}

string Vuelo::getDestino() const{
    return destino;
}
