#ifndef VUELO_H
#define VUELO_H

#include <string>
#include <vector>
using namespace std;

class Vuelo{

private:

    string codigo;
    string destino;
    int asientosTotales;
    vector<bool> asientosDisponibles;

public:

    Vuelo(const string& codigo, const string& destino, int capacidad);
    bool estaDisponible(int asiento) const;
    void ocuparAsiento(int asiento);
    string getCodigo() const;
    string getDestino() const;

};

#endif // VUELO_H
