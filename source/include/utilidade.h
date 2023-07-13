#ifndef UTILIDADE_H
#define UTILIDADE_H

#include <algorithm>
#include <iostream>
#include <random>
#include "vector.h"


/**
 * @brief Gera um número aleatório dentro de um intervalo.
 *
 * @param min O limite inferior do intervalo.
 * @param max O limite superior do intervalo.
 * @return Um número aleatório dentro do intervalo [min, max].
 */

double gerarNumeroAleatorio(double min, double max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0); 
    return dis(gen); 
}


/**
 * @brief Cria um vetor de pesos para distribuição de votos.
 *
 * @param qtd O número de pesos a serem gerados.
 * @param uniforme Define se a distribuição dos pesos será uniforme ou não. O valor padrão é false.
 * @return Um vetor de pesos para distribuição de votos.
 */
sc::vector<double> cria_vetor_pesos(int qtd, int uniforme = false){

    sc::vector<double> weights;
    
    if(!uniforme){
        double vetor_real_01[qtd+1];
        vetor_real_01[0] = 0;
        vetor_real_01[qtd] = 1;

        for(int i = 1; i < qtd; i++)
            vetor_real_01[i] = gerarNumeroAleatorio(0, 1);
    

        int size = sizeof(vetor_real_01)/sizeof(vetor_real_01[0]);
        std::sort(vetor_real_01, vetor_real_01+size); 
        
        for(int i = 0; i<qtd; i++)
            weights.push_back(vetor_real_01[i+1]-vetor_real_01[i]);

    }else
        for(int i=0; i<qtd; i++)
            weights.push_back(1);
    
    return weights;
} 

#endif