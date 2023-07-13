#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
#include <stdexcept>
#include <iostream>

/**
 * @brief Classe que implementa as especificações de candidados para a classe sistema majoritário
 * @authors Danillo Melo da Fonseca
 * @authors Eduarda Rodrigues Chiesa
 * @date 10/07/2023
*/

namespace sv {

class Candidato {
private:
  unsigned int ID;
  unsigned int qtd_votos;
  int ID_partido;

public:
  


/**
 * @brief Construtor da classe Candidato.
 *
 * Inicializa a quantidade de votos como zero.
 *
 * @return Uma instância da classe Candidato.
 */
 Candidato() {
  this->qtd_votos = 0;
}

/**
 * @brief Destrutor da classe Candidato.
 *
 * Libera os recursos associados a um objeto Candidato.
 */
  ~Candidato() {};


/**
 * @brief Define o ID do Candidato.
 *
 * @param novo_ID O novo ID a ser atribuído ao Candidato.
 * @return void
 */
  void setID(unsigned int novo_ID){ this->ID = novo_ID; }

  /**
 * @brief Define a quantidade de votos do Candidato.
 *
 * @param qtd_votos A nova quantidade de votos a ser atribuída ao Candidato.
 * @return void
 */
  void setVotos(unsigned int qtd_votos){ this->qtd_votos = qtd_votos; }


/**
 * @brief Define o partido do Candidato.
 *
 * @param partido O número do partido a ser atribuído ao Candidato.
 * @return void
 */
  void setPartido(unsigned int partido){ this->ID_partido = partido; }

  unsigned int getID() const { return this->ID; }
  unsigned int getPartido() const { return this->ID_partido; }
  unsigned int getVotos() const { return this->qtd_votos; }
  void addVoto() { this->qtd_votos += 1; }


/**
 * @brief Sobrecarga do operador de comparação maior (>) para a classe Candidato.
 *
 * @param other O Candidato a ser comparado.
 * @return true se o Candidato atual tiver mais votos do que o Candidato comparado, false caso contrário.
 */
  bool operator>(const Candidato& other) const {
    return this->qtd_votos > other.qtd_votos;
  }


/**
 * @brief Sobrecarga do operador de comparação menor (<) para a classe Candidato.
 *
 * @param other O Candidato a ser comparado.
 * @return true se o Candidato atual tiver menos votos do que o Candidato comparado, false caso contrário.
 */
  bool operator<(const Candidato& other) const {
    return this->qtd_votos < other.qtd_votos;
  }


/**
 * @brief Sobrecarga do operador de atribuição (=) para a classe Candidato.
 *
 * @param other O Candidato a ser atribuído.
 * @return Uma referência para o objeto Candidato atualizado.
 */
  Candidato& operator=(const Candidato& other) {
  if (this != &other) {
    this->ID = other.ID;
    this->qtd_votos = other.qtd_votos;
    this->ID_partido = other.ID_partido;
  }
  return *this;
}
  
  friend std::ostream& operator<<(std::ostream& os, const Candidato& candidato);
  
};

//unsigned int Candidato::ultimoID = 0;


/**
 * @brief Sobrecarga do operador de inserção (<<) para a classe Candidato.
 *
 * @param os O stream de saída onde o Candidato será inserido.
 * @param candidato O Candidato a ser inserido no stream de saída.
 * @return Uma referência para o stream de saída atualizado.
 */

std::ostream& operator<<(std::ostream& os, const Candidato& candidato) {
  os << "ID: " << candidato.getID() << " partido: " << candidato.getPartido() << " votos: " << candidato.qtd_votos;

  /*
  os << "ID: " << candidato.getID() << std::endl;
  os << "Partido: " << candidato.getPartido() << std::endl;
  os << "Quantidade de votos: " << candidato.qtd_votos << std::endl;
  */
  return os;
}

}  // namespace sv

#endif
