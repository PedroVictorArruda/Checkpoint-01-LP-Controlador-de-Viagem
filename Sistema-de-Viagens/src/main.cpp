#include <iostream>
#include "controllers/ControladorDeTransito.h"
#include <limits>

int main() {
    ControladorDeTransito controladorDeTransito;
    int opcao;
    
    while (true) {
        std::cout << "\n=== Sistema Controlador de Viagens ===\n";
        std::cout << "1. Cadastrar Cidade\n";
        std::cout << "2. Cadastrar Trajeto\n";
        std::cout << "3. Cadastrar Transporte\n";
        std::cout << "4. Cadastrar Passageiro\n";
        std::cout << "5. Listar Cidades\n";
        std::cout << "6. Listar Trajetos\n";
        std::cout << "7. Listar Transportes\n";
        std::cout << "8. Listar Passageiros\n";
        std::cout << "9. Iniciar Viagem\n";
        std::cout << "10. Avançar Horas de Viagem\n";
        std::cout << "11. Relatar Estado das Viagens\n";
        std::cout << "12. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        // Verifica se a opção está dentro do intervalo válido
        if (std::cin.fail() || opcao < 1 || opcao > 12) {
            std::cin.clear(); // Limpar o erro de entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar o buffer
            std::cout << "Obrigatório escolher uma opção.\n";
            continue; // Voltar ao início do loop
        }

        switch (opcao) {
            case 1: {
                std::string nomeCidade;
                std::cout << "Digite o nome da cidade: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, nomeCidade);
                controladorDeTransito.cadastrarCidade(nomeCidade);
                break;
            }
            case 2: {
                std::string nomeOrigem, nomeDestino;
                char tipo;
                int distancia;
                std::cout << "Digite o nome da cidade de origem: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, nomeOrigem);
                std::cout << "Digite o nome da cidade de destino: ";
                std::getline(std::cin, nomeDestino);
                std::cout << "Digite o tipo de trajeto (A para Aquático, T para Terrestre): ";
                std::cin >> tipo;
                std::cout << "Digite a distância do trajeto (em km): ";
                std::cin >> distancia;
                controladorDeTransito.cadastrarTrajeto(nomeOrigem, nomeDestino, tipo, distancia);
                break;
            }
            case 3: {
                std::string nomeTransporte, localAtual;
                char tipo;
                int capacidade, velocidade, distanciaEntreDescansos, tempoDescanso;
                std::cout << "Digite o nome do transporte: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, nomeTransporte);
                std::cout << "Digite o tipo do transporte (A para Aquático, T para Terrestre): ";
                std::cin >> tipo;
                std::cout << "Digite a capacidade de passageiros: ";
                std::cin >> capacidade;
                std::cout << "Digite a velocidade do transporte (km/h): ";
                std::cin >> velocidade;
                std::cout << "Digite a distância entre descansos (em km): ";
                std::cin >> distanciaEntreDescansos;
                std::cout << "Digite o tempo de descanso (em horas): ";
                std::cin >> tempoDescanso;
                std::cout << "Digite a cidade de origem do transporte: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, localAtual);
                controladorDeTransito.cadastrarTransporte(nomeTransporte, tipo, capacidade, velocidade, distanciaEntreDescansos, tempoDescanso, localAtual);
                break;
            }
            case 4: {
                std::string nomePassageiro, localAtual;
                std::cout << "Digite o nome do passageiro: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, nomePassageiro);
                std::cout << "Digite a cidade de origem do passageiro: ";
                std::getline(std::cin, localAtual);
                controladorDeTransito.cadastrarPassageiro(nomePassageiro, localAtual);
                break;
            }
            case 5:
                controladorDeTransito.listarCidades();
                break;
            case 6:
                controladorDeTransito.listarTrajetos();
                break;
            case 7:
                controladorDeTransito.listarTransportes();
                break;
            case 8:
                controladorDeTransito.listarPassageiros();
                break;
            case 9: {
                std::string nomeTransporte, nomeOrigem, nomeDestino;
                std::vector<std::string> nomesPassageiros;
                int numPassageiros;
                std::cout << "Digite o nome do transporte: ";
                std::cin.ignore(); // Limpar buffer
                std::getline(std::cin, nomeTransporte);
                std::cout << "Digite o nome da cidade de origem: ";
                std::getline(std::cin, nomeOrigem);
                std::cout << "Digite o nome da cidade de destino: ";
                std::getline(std::cin, nomeDestino);
                std::cout << "Quantos passageiros irão viajar? ";
                std::cin >> numPassageiros;
                nomesPassageiros.resize(numPassageiros);
                for (int i = 0; i < numPassageiros; ++i) {
                    std::cout << "Digite o nome do passageiro " << (i + 1) << ": ";
                    std::cin.ignore();
                    std::getline(std::cin, nomesPassageiros[i]);
                }
                controladorDeTransito.iniciarViagem(nomeTransporte, nomesPassageiros, nomeOrigem, nomeDestino);
                break;
            }
            case 10: {
                int horas;
                std::cout << "Quantas horas deseja avançar? ";
                std::cin >> horas;
                controladorDeTransito.avancarHoras(horas);
                break;
            }
            case 11:
                controladorDeTransito.relatarEstadoViagem();
                break;
            case 12:
                std::cout << "Saindo...\n";
                return 0;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    }

    return 0;
}
