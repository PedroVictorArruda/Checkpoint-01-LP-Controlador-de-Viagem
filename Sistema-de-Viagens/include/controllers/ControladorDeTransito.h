#ifndef CONTROLADORDETRANSITO_H
#define CONTROLADORDETRANSITO_H

#include "models/Cidade.h"
#include "models/Trajeto.h"
#include "models/Transporte.h"
#include "models/Passageiro.h"
#include "models/Viagem.h"  // Adicionando a classe Viagem
#include <vector>
#include <string>

class ControladorDeTransito
{
private:
    std::vector<Cidade *> cidades;
    std::vector<Trajeto *> trajetos;
    std::vector<Transporte *> transportes;
    std::vector<Passageiro *> passageiros;
    std::vector<Viagem *> viagens;  // Adicionando o vetor para armazenar viagens

public:
    ~ControladorDeTransito();

    // Cadastro de cidade, com a opção de exibir ou não a mensagem
    void cadastrarCidade(const std::string &nome, bool exibirMensagem = true);

    // Cadastro de trajeto
    void cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia);

    // Cadastro de transporte
    void cadastrarTransporte(const std::string &nome, char tipo, int capacidade, int velocidade,
                             int distanciaEntreDescansos, int tempoDescanso, const std::string &localAtual);

    // Cadastro de passageiro
    void cadastrarPassageiro(const std::string &nome, const std::string &localAtual);

    // Listagem de cidades, trajetos, transportes e passageiros
    void listarCidades() const;
    void listarTrajetos() const;
    void listarTransportes() const;
    void listarPassageiros() const;

    // Funções para gerenciar viagens
    void iniciarViagem(const std::string &nomeTransporte, const std::vector<std::string> &nomesPassageiros, const std::string &nomeOrigem, const std::string &nomeDestino);
    void avancarHoras(int horas);
    void relatarEstadoViagem() const;

    // Funções de carregar e salvar as cidades
    void carregarCidades();
    void salvarCidades() const;
};

#endif

