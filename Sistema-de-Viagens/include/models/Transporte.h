#ifndef TRANSPORTE_H
#define TRANSPORTE_H
#include "models/Cidade.h"
#include <string>
class Transporte {
private:
    std::string nome;
    char tipo; // 'A' para Aquático, 'T' para Terrestre
    int capacidade;
    int velocidade;
    int distanciaEntreDescansos;
    int tempoDescanso;
    Cidade* localAtual;
public:
    Transporte(const std::string& nome, char tipo, int capacidade, int velocidade,
               int distanciaEntreDescansos, int tempoDescanso, Cidade* localAtual);
    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* novaLocalizacao);
};
#endif