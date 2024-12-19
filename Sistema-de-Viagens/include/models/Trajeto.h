#ifndef TRAJETO_H
#define TRAJETO_H
#include "models/Cidade.h"
class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo;
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};
#endif