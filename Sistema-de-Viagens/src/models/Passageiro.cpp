#include "models/Passageiro.h"
Passageiro::Passageiro(const std::string& nome, Cidade* localAtual) : nome(nome), localAtual(localAtual) {}
std::string Passageiro::getNome() const { return nome; }
Cidade* Passageiro::getLocalAtual() const { return localAtual; }
void Passageiro::setLocalAtual(Cidade* novaLocalizacao) { localAtual = novaLocalizacao; }
