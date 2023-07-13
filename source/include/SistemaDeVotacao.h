#ifndef SISTEMADEVOTACAO_H
#define SISTEMADEVOTACAO_H

#include <string>
#include "vector.h"
#include "Candidato.h"
#include "utilidade.h"
#include "Ordenacao.h"
#include "Menu.h"

/**
 * @brief A presente classe implementa um sistema majoritário de votação
 * @authors Danillo Melo da Fonseca
 * @authors Eduarda Rodrigues Chiesa
 * @date 10/07/2023
*/

namespace sv { //sv: sistema de votação
    class SistemaDeVotacao {    
    public: 
        Menu menu;
    static bool compare(const Candidato& a, const Candidato& b) {
            return a < b;
    }


/**
 * @brief Realiza um sistema majoritário para determinar o vencedor com base em votos totais.
 *
 * @param candidatos Um vetor de objetos da classe Candidato representando os candidatos.
 * @param votos_totais O número total de votos.
 * @return Um vetor de objetos da classe Candidato contendo o resultado do sistema majoritário.
 */
    sc::vector<Candidato> sistemaMajoritario(sc::vector<Candidato> candidatos, int votos_totais){
            sc::vector<Candidato> resultado;
            int metade_votos = votos_totais/2;
                
            if(candidatos.size()==1){
            resultado.push_back(candidatos[0]);
            return resultado;
            }
            sa::merge_sort(&candidatos[0],&candidatos[candidatos.size()], compare);

            Candidato ultimo = candidatos[candidatos.size()-1];
            Candidato penultimo = candidatos[candidatos.size()-2];

            if( ultimo.getVotos() >  metade_votos){
                resultado.push_back(ultimo);
                return resultado;
            }

            resultado.push_back(ultimo);
            resultado.push_back(penultimo);
            return resultado;

        }
        //sc::vector<Candidato>


        /**
 * @brief Simula uma votação com base em uma quantidade de candidatos, eleitores e escolha de distribuição.
 *
 * @param qtd_candidatos O número de candidatos.
 * @param qtd_eleitores O número de eleitores.
 * @param escolha_distribuicao A escolha da distribuição de pesos. Os valores possíveis são:
 *        - 1: Distribuição de pesos verdadeiros.
 *        - 2: Distribuição de pesos falsos.
 *        - 3: Distribuição de pesos personalizados inseridos pelo usuário.
 * @param vetor_de_candidatos Um vetor de objetos da classe Candidato representando os candidatos.
 * @return Um vetor de objetos da classe Candidato atualizado com o resultado da simulação de votação.
 */

     sc::vector<sv::Candidato> simular_votacao(int qtd_candidatos,
                             int qtd_eleitores,
                             int esolha_distribuicao,
                             sc::vector<sv::Candidato> vetor_de_candidatos                     
                             ){
            
            for(int i=0; i<vetor_de_candidatos.size(); i++)
                vetor_de_candidatos[i].setVotos(0);

            sc::vector<double> pesos;

            if(esolha_distribuicao == 1)
                pesos = cria_vetor_pesos(qtd_candidatos, true);

            if(esolha_distribuicao == 2)
                pesos = cria_vetor_pesos(qtd_candidatos, false);

            if(esolha_distribuicao == 3){
                
                std::cout << "\n================================================\n";
        std::cout << "  |    \033[1;35mDistribuição de votos por candidato\033[0m   |"; // Texto roxo (código de escape ANSI: \033[1;35m)
                std::cout << "\n================================================\n\n";
                std::cout << "\033[1;33m--> Preencha o vetor de pesos, cada entrada representa a chance de um candidato de receber um voto. Quanto maior o número, maior a chance. Existem: " << qtd_candidatos << " candidatos.\033[0m \n\n"; // Texto amarelo (código de escape ANSI: \033[1;33m)
                for(int i = 0; i<qtd_candidatos; i++){ 
                    double input;
                    std::cout << "Peso para o candidato de ID: " << vetor_de_candidatos[i].getID()+1 << " do partido " << vetor_de_candidatos[i].getPartido()+1 << " : ";
                    std::cin >> input;
                    pesos.push_back(input);
                }
            }

            std::random_device rd;

            std::mt19937 gen(rd());
            
            std::discrete_distribution<> dis(pesos.begin(), pesos.end());

            for(int i=0; i<qtd_eleitores; i++){
                int id_voto_aleatorio = dis(gen);
                vetor_de_candidatos[id_voto_aleatorio].addVoto();
            }

            //resultado = sistemaMajoritario(vetor_de_candidatos, qtd_eleitores);

            return vetor_de_candidatos;
        }
    };
 
} // fim do namespace

#endif