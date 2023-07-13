#include <iostream>
#include <algorithm>
#include <random>

#include "include/Candidato.h"
#include "include/SistemaDeVotacao.h"
#include "include/Menu.h"
#include "include/utilidade.h"

#include "include/list.h"
#include "include/vector.h"

#include "include/Buscas.h"
#include "include/Ordenacao.h"





int main(){

sv::Menu menu;

    menu.exibirMenu();

    int qtd_eleitores = menu.getQuantidadeEleitores();
    int qtd_partidos = menu.getQuantidadePartidos();
    int qtd_candidatos = menu.getQuantidadeCandidatos();
    std::vector<int> candidatosPorPartido = menu.getCandidatosPorPartido();

    sc::vector<sv::Candidato> candidatos;

    for(int p=0, id=0; p<qtd_partidos; p++){
        for (int i = 0; i < candidatosPorPartido[p]; i++) {
            sv::Candidato generico;
            generico.setID(id);
            generico.setPartido(p);
            candidatos.push_back(generico);
            id++;
        }
    }

    int escolha = 0;

    std::cout << '\n';
    std::cout << "Escolha como se dará a distribuição dos votos:\n";
    std::cout << "================================================\n";
    std::cout << "1) distribuição discreta uniforme automática\n";
    std::cout << "2) distribuição discreta não uniforme automática\n";
    std::cout << "3) distribuição manual\n";
    std::cout << "================================================\n";
    std::cout << "\n-->";
    std::cin >> escolha;

    sv::SistemaDeVotacao maj;

    sc::vector<sv::Candidato> primeiroTurno;

        std::cout << "\n================================================\n";
        std::cout << "  |    \033[1;35mCandidatos que participarão \033[0m   |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
        std::cout << "================================================\n\n";

    for(int i=0; i<candidatos.size(); i++)
    std::cout << "  Candidato de ID: " << candidatos[i].getID() << " do partido: " << candidatos[i].getPartido() << std::endl;

    candidatos = maj.simular_votacao(qtd_candidatos, qtd_eleitores, escolha, candidatos);//realiza a votação

    primeiroTurno = maj.sistemaMajoritario(candidatos,qtd_eleitores);//analiza o resultado da votação

    std::cout << "\n=======================================================\n";
    std::cout << "  |  \033[1;35mConfira abaixo os resultados do primeiro turno\033[0m |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
    std::cout << "=======================================================\n\n";

    for(int i=0; i<candidatos.size(); i++)std::cout << "  Candidato de " <<  candidatos[i] <<std::endl;

     std::cout << "\n=========================================================\n";
    std::cout << "  |  \033[1;35mVencedor(es) do primeiro turno: "<< primeiroTurno.size() << ", confira abaixo\033[0m |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
    std::cout << "=========================================================\n\n";

    for(int i=0; i<primeiroTurno.size(); i++) std::cout << "  Canididato de " << primeiroTurno[i] << std::endl;

    sc::vector<sv::Candidato> segundoTurno;
    sc::vector<sv::Candidato> candidatosSegundoTurno;

    if(candidatos.size()>1){
          std::cout << "\033[1;31m\n! Nenhum candidato atingiu + de 50% de votos. Será necessário um segundo turno !\033[0m" << "\n";



        //criamos uma copia do vector primeiro turno que será utilizado como base para o segundo turno
        for(int i=0; i < primeiroTurno.size(); i++)
            candidatosSegundoTurno.push_back(primeiroTurno[i]);

        candidatosSegundoTurno = maj.simular_votacao(2,qtd_eleitores, escolha, candidatosSegundoTurno);

        segundoTurno = maj.sistemaMajoritario(candidatosSegundoTurno, qtd_eleitores);

    std::cout << "\n=======================================================\n";
    std::cout << "  |  \033[1;35mConfira abaixo os resultados do segundo turno\033[0m |\n"; // Texto roxo (código de escape ANSI: \033[1;35m)
    std::cout << "=======================================================\n\n";


        for(int i=0; i<candidatosSegundoTurno.size(); i++)std::cout << "  Candidato de " << candidatosSegundoTurno[i] <<std::endl;

         std::cout << "\033[1;31m\n! Vencedor do segundo turno !\033[0m" << "\n\n";

        std::cout << "=======================================================\n";
        std::cout << "  Candidato de " <<  segundoTurno[0] << "\n"; 
        std::cout << "=======================================================\n\n";
    }


}