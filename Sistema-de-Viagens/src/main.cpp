#include <iostream>
#include "controllers/ControladorDeTransito.h"

int main() {
    ControladorDeTransito controlador;
    controlador.carregarCidades();
    int opcao;

    do {
        std::cout << "\n=== Sistema Controlador de Viagens ===\n";
        std::cout << "1. Cadastrar Cidade\n";
        std::cout << "2. Cadastrar Trajeto\n";
        std::cout << "3. Listar Cidades\n";
        std::cout << "4. Listar Trajetos\n";
        std::cout << "5. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                std::string nome;
                std::cout << "Nome da cidade: ";
                std::cin >> nome;
                controlador.cadastrarCidade(nome,true);
                break;
            }
            case 2: {
                std::string origem, destino;
                char tipo;
                int distancia;
                std::cout << "Cidade de origem: ";
                std::cin >> origem;
                std::cout << "Cidade de destino: ";
                std::cin >> destino;
                std::cout << "Tipo (A/T): ";
                std::cin >> tipo;
                std::cout << "Distância em km: ";
                std::cin >> distancia;
                controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
                break;
            }
            case 3:
                controlador.listarCidades();
                break;
            case 4:
                controlador.listarTrajetos();
                break;
            case 5:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    } while (opcao != 5);

    return 0;
}