#include "controllers/ControladorDeTransito.h"
#include <fstream>
#include <iostream>

#define ARQUIVO_CIDADES "data/cidades.txt"

ControladorDeTransito::~ControladorDeTransito() {
    for (Cidade* cidade : cidades) {
        delete cidade;
    }
    for (Trajeto* trajeto : trajetos) {
        delete trajeto;
    }
}

void ControladorDeTransito::cadastrarCidade(const std::string &nome, bool exibirMensagem) {
    cidades.push_back(new Cidade(nome));
    if (exibirMensagem) {
        std::cout << "Cidade cadastrada: " << nome << "\n";
    }
}

void ControladorDeTransito::cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia) {
    // Procurar as cidades no vetor de cidades
    Cidade* cidadeOrigem = nullptr;
    Cidade* cidadeDestino = nullptr;

    // Encontrar a cidade de origem
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nomeOrigem) {
            cidadeOrigem = cidade;
            break;
        }
    }

    // Encontrar a cidade de destino
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nomeDestino) {
            cidadeDestino = cidade;
            break;
        }
    }

    // Verifica se as cidades foram encontradas
    if (cidadeOrigem && cidadeDestino) {
        // Cria o trajeto
        trajetos.push_back(new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia));
        std::cout << "Trajeto de " << nomeOrigem << " para " << nomeDestino << " cadastrado!" << std::endl;
    } else {
        std::cerr << "Erro: Uma ou ambas as cidades não foram encontradas." << std::endl;
    }
}

void ControladorDeTransito::listarCidades() const {
    for (const auto& cidade : cidades) {
        std::cout << cidade->getNome() << std::endl;
    }
}

void ControladorDeTransito::listarTrajetos() const {
    for (const auto& trajeto : trajetos) {
        std::cout << trajeto->getOrigem()->getNome() << " -> "
                  << trajeto->getDestino()->getNome() << " (" 
                  << trajeto->getTipo() << ") "
                  << trajeto->getDistancia() << " km" << std::endl;
    }
}

void ControladorDeTransito::carregarCidades() {
    std::ifstream arquivo(ARQUIVO_CIDADES);
    if (!arquivo.is_open()) {
        std::cerr << "Aviso: Não foi possível abrir o arquivo de cidades. Talvez ele não exista ainda." << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            cadastrarCidade(linha, false); // Não exibe mensagem ao carregar
        }
    }
    arquivo.close();
    std::cout << "Cidades carregadas com sucesso!" << std::endl;
}

void ControladorDeTransito::salvarCidades() const {
    std::ofstream arquivo(ARQUIVO_CIDADES, std::ios::trunc);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo para salvar cidades." << std::endl;
        return;
    }

    for (const auto& cidade : cidades) {
        arquivo << cidade->getNome() << "\n";
    }
    arquivo.close();
    std::cout << "Cidades salvas com sucesso!" << std::endl;
}
