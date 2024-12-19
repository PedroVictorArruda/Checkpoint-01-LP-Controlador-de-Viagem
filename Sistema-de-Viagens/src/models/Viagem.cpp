#include "models/Viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), horasEmTransito(0), emAndamento(false) {}

void Viagem::iniciarViagem() {
    if (emAndamento) {
        std::cout << "Viagem já está em andamento!\n";
        return;
    }
    emAndamento = true;
    horasEmTransito = 0;
    std::cout << "Viagem iniciada de " << origem->getNome() << " para " << destino->getNome() << " usando " << transporte->getNome() << ".\n";
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) {
        std::cout << "Erro: A viagem ainda não foi iniciada.\n";
        return;
    }
    horasEmTransito += horas;
    int distanciaPercorrida = horas * transporte->getVelocidade();
    if (distanciaPercorrida >= transporte->getDistanciaEntreDescansos()) {
        horasEmTransito += transporte->getTempoDescanso();
        std::cout << "O transporte precisou parar para descanso.\n";
    }
    std::cout << "A viagem avançou " << horas << " horas.\n";

    if (horasEmTransito * transporte->getVelocidade() >= destino->getNome().size() * 100) {
        emAndamento = false;
        std::cout << "Viagem concluída!\n";
    }
}

void Viagem::relatarEstado() const {
    if (!emAndamento) {
        std::cout << "A viagem não está em andamento.\n";
        return;
    }
    std::cout << "Viagem em andamento há " << horasEmTransito << " horas.\n";
}

bool Viagem::isEmAndamento() const {
    return emAndamento;
}

std::string Viagem::getResumo() const {
    return "Viagem de " + origem->getNome() + " para " + destino->getNome() + ", usando " + transporte->getNome();
}