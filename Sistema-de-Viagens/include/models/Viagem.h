#ifndef VIAGEM_H
#define VIAGEM_H

#include "models/Cidade.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"
#include "Trajeto.h"
#include <vector>
#include <string>

class Viagem {
private:
    Trajeto* trajeto;
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    int horasEmTransito;
    bool emAndamento;
    bool chegada;

public:
    Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino);

    // Funções principais
    bool iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;
    void registrarChegada();

    // Função auxiliar
    std::string getResumo() const;

    // Calcular o melhor trajeto entre as cidades
    static Trajeto* calcularMelhorTrajeto(Cidade* origem, Cidade* destino, const std::vector<Trajeto*>& trajetos);
};

#endif

