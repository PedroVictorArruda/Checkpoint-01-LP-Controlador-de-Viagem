#include "models/Viagem.h"
#include <iostream>
#include <climits>

Viagem::Viagem(Transporte* transporte, const std::vector<Passageiro*>& passageiros, Cidade* origem, Cidade* destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino),
      horasEmTransito(0), emAndamento(false), chegada(false) {}

bool Viagem::iniciarViagem() {
    if (emAndamento) {
        std::cout << "Viagem já está em andamento!\n";
        return false;
    }
    
    // Verifica se o transporte está na cidade de origem
    if (transporte->getLocalAtual() != origem) {
        std::cout << "Erro: O transporte não está na cidade de origem (" << origem->getNome() << ").\n";
        return false;
    }

    emAndamento = true;
    horasEmTransito = 0;
    std::cout << "Viagem iniciada de " << origem->getNome() << " para " << destino->getNome() << " usando " << transporte->getNome() << ".\n";
    return true;
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

    // Verifica se a viagem chegou ao destino
    if (distanciaPercorrida >= destino->getNome().size() * 100) {
        registrarChegada();
    } else {
        std::cout << "A viagem avançou " << horas << " horas.\n";
    }
}

void Viagem::relatarEstado() const {
    if (!emAndamento) {
        std::cout << "A viagem não está em andamento.\n";
        return;
    }
    if (chegada) {
        std::cout << "A viagem foi concluída! A viagem chegou a " << destino->getNome() << ".\n";
    } else {
        std::cout << "Viagem em andamento há " << horasEmTransito << " horas.\n";
    }
}

bool Viagem::isEmAndamento() const {
    return emAndamento && !chegada;
}

void Viagem::registrarChegada() {
    chegada = true;
    emAndamento = false;
    std::cout << "O transporte chegou em " << destino->getNome() << ".\n";
}

std::string Viagem::getResumo() const {
    return "Viagem de " + origem->getNome() + " para " + destino->getNome() + ", usando " + transporte->getNome();
}

// Função para calcular o melhor trajeto entre as cidades
Trajeto* Viagem::calcularMelhorTrajeto(Cidade* origem, Cidade* destino, const std::vector<Trajeto*>& trajetos) {
    Trajeto* melhorTrajeto = nullptr;
    int melhorDistancia = INT_MAX;

    for (const auto& trajeto : trajetos) {
        if ((trajeto->getOrigem() == origem) && (trajeto->getDestino() == destino)) {
            int distancia = trajeto->getDistancia();
            if (distancia < melhorDistancia) {
                melhorDistancia = distancia;
                melhorTrajeto = trajeto;
            }
        }
    }

    return melhorTrajeto;
}
