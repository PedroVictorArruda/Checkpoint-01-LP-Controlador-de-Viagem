#include "controllers/ControladorDeTransito.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#define ARQUIVO_CIDADES "data/cidades.txt"

ControladorDeTransito::~ControladorDeTransito() {
    // Deletando as cidades, trajetos, transportes, passageiros e viagens
    for (Cidade* cidade : cidades) {
        delete cidade;
    }
    for (Trajeto* trajeto : trajetos) {
        delete trajeto;
    }
    for (Transporte* transporte : transportes) {
        delete transporte;
    }
    for (Passageiro* passageiro : passageiros) {
        delete passageiro;
    }
    for (Viagem* viagem : viagens) {
        delete viagem;
    }
}

// Cadastro de cidade
void ControladorDeTransito::cadastrarCidade(const std::string &nome, bool exibirMensagem) {
    cidades.push_back(new Cidade(nome));
    if (exibirMensagem) {
        std::cout << "Cidade cadastrada: " << nome << "\n";
    }
}

// Cadastro de trajeto
void ControladorDeTransito::cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia) {
    Cidade* cidadeOrigem = nullptr;
    Cidade* cidadeDestino = nullptr;

    // Procurar as cidades
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nomeOrigem) {
            cidadeOrigem = cidade;
            break;
        }
    }
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nomeDestino) {
            cidadeDestino = cidade;
            break;
        }
    }

    // Verifica se as cidades foram encontradas
    if (cidadeOrigem && cidadeDestino) {
        trajetos.push_back(new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia));
        std::cout << "Trajeto cadastrado de " << nomeOrigem << " para " << nomeDestino << "\n";
    } else {
        std::cerr << "Erro: Uma ou ambas as cidades não foram encontradas.\n";
    }
}

// Cadastro de transporte
void ControladorDeTransito::cadastrarTransporte(const std::string &nome, char tipo, int capacidade, int velocidade,
                                                int distanciaEntreDescansos, int tempoDescanso, const std::string &localAtual) {
    Cidade* cidadeLocal = nullptr;
    for (auto& cidade : cidades) {
        if (cidade->getNome() == localAtual) {
            cidadeLocal = cidade;
            break;
        }
    }

    if (cidadeLocal) {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distanciaEntreDescansos, tempoDescanso, cidadeLocal));
        std::cout << "Transporte " << nome << " cadastrado com sucesso!\n";
    } else {
        std::cerr << "Erro: Cidade de origem do transporte não encontrada.\n";
    }
}

// Cadastro de passageiro
void ControladorDeTransito::cadastrarPassageiro(const std::string &nome, const std::string &localAtual) {
    Cidade* cidadeLocal = nullptr;
    for (auto& cidade : cidades) {
        if (cidade->getNome() == localAtual) {
            cidadeLocal = cidade;
            break;
        }
    }

    if (cidadeLocal) {
        passageiros.push_back(new Passageiro(nome, cidadeLocal));
        std::cout << "Passageiro " << nome << " cadastrado com sucesso!\n";
    } else {
        std::cerr << "Erro: Cidade de localização do passageiro não encontrada.\n";
    }
}

// Listar cidades
void ControladorDeTransito::listarCidades() const {
    if (cidades.empty()) {
        std::cout << "Nenhuma cidade cadastrada.\n";
        return;
    }

    std::cout << "Cidades cadastradas:\n";
    for (const auto& cidade : cidades) {
        std::cout << "Nome: " << cidade->getNome() << "\n";
    }
}

// Listar trajetos
void ControladorDeTransito::listarTrajetos() const {
    if (trajetos.empty()) {
        std::cout << "Nenhum trajeto cadastrado.\n";
        return;
    }

    std::cout << "Trajetos cadastrados:\n";
    for (const auto& trajeto : trajetos) {
        std::cout << "Origem: " << trajeto->getOrigem()->getNome() 
                  << " -> Destino: " << trajeto->getDestino()->getNome() 
                  << ", Tipo: " << (trajeto->getTipo() == 'A' ? "Aquático" : "Terrestre") 
                  << ", Distância: " << trajeto->getDistancia() << " km\n";
    }
}

// Listar passageiros
void ControladorDeTransito::listarPassageiros() const {
    if (passageiros.empty()) {
        std::cout << "Nenhum passageiro cadastrado.\n";
        return;
    }

    std::cout << "Passageiros cadastrados:\n";
    for (const auto& passageiro : passageiros) {
        std::cout << "Nome: " << passageiro->getNome() << ", Local Atual: " << passageiro->getLocalAtual()->getNome() << "\n";
    }
}

// Listar transportes
void ControladorDeTransito::listarTransportes() const {
    if (transportes.empty()) {
        std::cout << "Não há transportes cadastrados.\n";
        return;
    }

    std::cout << "\n=== Transportes Cadastrados ===\n";
    for (const auto& transporte : transportes) {
        std::cout << "Nome: " << transporte->getNome() << "\n"
                  << "Tipo: " << (transporte->getTipo() == 'A' ? "Aquático" : "Terrestre") << "\n"
                  << "Capacidade: " << transporte->getCapacidade() << " passageiros\n"
                  << "Velocidade: " << transporte->getVelocidade() << " km/h\n"
                  << "Distância entre descansos: " << transporte->getDistanciaEntreDescansos() << " km\n"
                  << "Tempo de descanso: " << transporte->getTempoDescanso() << " horas\n"
                  << "Local Atual: " << transporte->getLocalAtual()->getNome() << "\n"
                  << "--------------------------------\n";
    }
}

// Iniciar viagem
void ControladorDeTransito::iniciarViagem(const std::string &nomeTransporte, const std::vector<std::string> &nomesPassageiros, const std::string &nomeOrigem, const std::string &nomeDestino) {
    // Procurando transporte, passageiros e cidades
    Transporte* transporte = nullptr;
    for (auto& t : transportes) {
        if (t->getNome() == nomeTransporte) {
            transporte = t;
            break;
        }
    }

    if (!transporte) {
        std::cerr << "Erro: Transporte não encontrado.\n";
        return;
    }

    Cidade* origem = nullptr;
    Cidade* destino = nullptr;
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nomeOrigem) {
            origem = cidade;
        }
        if (cidade->getNome() == nomeDestino) {
            destino = cidade;
        }
    }

    if (!origem || !destino) {
        std::cerr << "Erro: Cidades de origem ou destino não encontradas.\n";
        return;
    }

    std::vector<Passageiro*> passageirosViagem;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* passageiro = nullptr;
        for (auto& p : passageiros) {
            if (p->getNome() == nome) {
                passageiro = p;
                break;
            }
        }
        if (passageiro) {
            passageirosViagem.push_back(passageiro);
        } else {
            std::cerr << "Passageiro " << nome << " não encontrado.\n";
        }
    }

    Viagem* viagem = new Viagem(transporte, passageirosViagem, origem, destino);
    viagens.push_back(viagem);
    viagem->iniciarViagem();
}

// Avançar horas na viagem
void ControladorDeTransito::avancarHoras(int horas) {
    for (auto& viagem : viagens) {
        if (viagem->isEmAndamento()) {
            viagem->avancarHoras(horas);
            return;
        }
    }
    std::cerr << "Erro: Nenhuma viagem está em andamento.\n";
}

// Relatar estado da viagem
void ControladorDeTransito::relatarEstadoViagem() const {
    for (const auto& viagem : viagens) {
        viagem->relatarEstado();
    }
}

// Carregar cidades
void ControladorDeTransito::carregarCidades() {
    std::ifstream arquivo("data/cidades.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Aviso: Não foi possível abrir o arquivo de cidades.\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            cadastrarCidade(linha, false);
        }
    }
    arquivo.close();
    std::cout << "Cidades carregadas com sucesso!\n";
}
