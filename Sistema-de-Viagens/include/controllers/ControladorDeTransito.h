#ifndef CONTROLADORDETRANSITO_H
#define CONTROLADORDETRANSITO_H

#include "models/Cidade.h"
#include "models/Trajeto.h"
#include <vector>
#include <string>

class ControladorDeTransito
{
private:
    std::vector<Cidade *> cidades;
    std::vector<Trajeto *> trajetos;

public:
    ~ControladorDeTransito();

    // Cadastro de cidade, com a opção de exibir ou não a mensagem
    void cadastrarCidade(const std::string &nome, bool exibirMensagem = true);

    // Cadastro de trajeto
    void cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia);

    // Listagem de cidades e trajetos
    void listarCidades() const;
    void listarTrajetos() const;

    // Funções de carregar e salvar as cidades
    void carregarCidades();
    void salvarCidades() const;
};

#endif
