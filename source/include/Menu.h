#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>


/**
 * @brief Classe Menu
 * @authors Danillo Melo da Fonseca
 * @authors Eduarda Rodrigues Chiesa
 * @date 10/07/2023
*/

namespace sv {

class Menu {
public:

    int quantidadeCandidatos;
    int quantidadeEleitores;
    int quantidadePartidos;
    std::vector<int> candidatosPorPartido;

    Menu() : quantidadeCandidatos(0), quantidadeEleitores(0), quantidadePartidos(0) {}

    void exibirMenu() {
        limparTela();
        exibirBorda();
        exibirCabecalho();
        aguardarEntrada();
        exibirInterfaceDados();
    }

    void aguardarEntrada() {
        std::cin.get();
    }

    void exibirInterfaceDados() {
        limparTela();
        exibirBorda();
        exibirCabecalhoDados();
        exibirBorda();
        preencherQuantidadeEleitores();
        preencherQuantidadePartidos();
        exibirBorda();
        exibirInterfaceDistribuicao();
    }

    int getQuantidadeEleitores() const {
        return quantidadeEleitores;
    }

    int getQuantidadePartidos() const {
        return quantidadePartidos;
    }

    std::vector<int> getCandidatosPorPartido() const {
        return this->candidatosPorPartido;
    }

    int getQuantidadeCandidatos(){
        return this->quantidadeCandidatos;
    }

    void incrementoCandidatos(int qtd){
        this->quantidadeCandidatos+=qtd;
    }


private:
  
    void limparTela() {
        std::cout << "\033[2J\033[1;1H"; // Limpa a tela do terminal
    }

    void exibirBorda() {
        std::cout << "================================================\n";
    }

    void exibirSeta() {
        std::cout << "--> ";
    }

    void exibirCabecalho() {
        std::cout << " |      \033[1;35mSimulação de Sistemas de Votação\033[0m      |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
        exibirBorda();
        std::cout << "\n    \033[1;33mEntre com qualquer tecla para continuar\033[0m     \n\n"; // Texto amarelo (código de escape ANSI: \033[1;33m)
        exibirSeta();
    }

    void exibirCabecalhoDados() {
        std::cout << "   |   \033[1;35mPreenchendo dados sobre a simulação\033[0m   |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
    }

    void preencherQuantidadeEleitores() {
        std::cout << "\n\033[1;33m--> Quantidade de eleitores: \033[0m"; // Texto amarelo (código de escape ANSI: \033[1;33m)
        std::cin >> quantidadeEleitores;
        std::cin.ignore(); // Limpa o caractere de nova linha do buffer
    }

    void preencherQuantidadePartidos() {
        std::cout << "\033[1;33m--> Quantidade de partidos: \033[0m"; // Texto amarelo (código de escape ANSI: \033[1;33m)
        std::cin >> quantidadePartidos;
        std::cin.ignore(); // Limpa o caractere de nova linha do buffer
    }

    void exibirInterfaceDistribuicao() {
        limparTela();
        exibirBorda();
        exibirCabecalhoDistribuicao();
        exibirBorda();
        preencherCandidatosPorPartido();
        exibirBorda();
    }

    void exibirCabecalhoDistribuicao() {
        exibirBorda();
        std::cout << "   |   \033[1;35mDistribuindo candidatos por partido\033[0m   |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
    }

   void preencherCandidatosPorPartido() {
    candidatosPorPartido.clear();

    for (int i = 0; i < quantidadePartidos; i++) {
        limparTela(); // Limpa a tela antes de cada nova entrada
        exibirCabecalhoDistribuicao();
        exibirBorda();

        std::cout << "\033[1;33m--> Quantidade de candidatos para o partido [" << i << "] : \033[0m"; // Texto amarelo (código de escape ANSI: \033[1;33m)
        int quantidade;
        std::cin >> quantidade;
        candidatosPorPartido.push_back(quantidade);
        incrementoCandidatos(quantidade);
        std::cin.ignore(); // Limpa o caractere de nova linha do buffer
    }
}

};

}  // namespace sv

#endif  // MENU_H
