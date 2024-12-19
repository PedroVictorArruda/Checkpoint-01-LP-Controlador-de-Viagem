#ifndef VIAGEM_H
#define VIAGEM_H
#include "models/Transporte.h"
#include "models/Passageiro.h"
#include "models/Cidade.h"
#include <vector>
#include <string>

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    int horasEmTransito;
    bool emAndamento;

public:
    Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;
    std::string getResumo() const;
};

#endif
