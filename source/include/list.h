#ifndef LIST_H
#define LIST_H

#include <iostream> // cout, endl

#include <algorithm> // copy
#include <cassert>   // assert()
#include <cstddef>   // std::ptrdiff_t
#include <iterator>  // bidirectional_iterator_tag
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as
               // STL).
/*!
 * A class representing a biderectional iterator defined over a linked list.
 *
 * \note
 * This iterator only works for traversing elements inside the same list.
 *
 * This class is incomplete and it is provided "as is".
 *
 */

// CLASSE LISTA

template <typename T> class list {
private:
  //=== the data node.
  struct Node {
    T data; // Tipo de informação a ser armazenada no container.
    Node *next;
    Node *prev;

    Node(const T &d = T{}, Node *n = nullptr, Node *p = nullptr)
        : data{d}, next{n}, prev{p} { /* empty */
    }
  };

  //=== The iterator classes.
public:
  class const_iterator : public std::bidirectional_iterator_tag {
    //=== Some aliases to help writing a clearer code.
  public:
    using value_type = T;  //!< The type of the value stored in the list.
    using pointer = T *;   //!< Pointer to the value.
    using reference = T &; //!< reference to the value.
    using const_reference = const T &; //!< const reference to the value.
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

  private:
    Node *m_ptr; //!< The raw pointer.

  public:
    const_iterator(Node *ptr = nullptr) : m_ptr(ptr) {}
    ~const_iterator() = default;
    const_iterator(const const_iterator &) = default;
    const_iterator &operator=(const const_iterator &) = default;
    reference operator*() { return m_ptr->data; }
    const_reference operator*() const { return m_ptr->data; }
    const_iterator operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator aux = *this;
      ++(*this);
      return aux;
    }
    const_iterator operator--() {
      m_ptr = m_ptr->prev;
      return *this;
    }
    const_iterator operator--(int) { 
      const_iterator aux = *this;
      --(*this);
      return aux;
    }
    bool operator==(const const_iterator &rhs) const { 
      return m_ptr == rhs.m_ptr;
    }
    bool operator!=(const const_iterator &rhs) const { 
      return !(m_ptr == rhs.m_ptr);
    }

    //=== Other methods that you might want to implement.
    /// it += 3; // Go forward  3 positions within the container.
    const_iterator operator+=(difference_type step) {
      if (step >= 0) {
        for (difference_type i = 0; i < step && m_ptr != nullptr; ++i) {
          m_ptr = m_ptr->next;
        }
      } else {
        for (difference_type i = 0; i > step && m_ptr != nullptr; --i) {
          m_ptr = m_ptr->prev;
        }
        return *this;
      }
    }
    /// it -= 3; // Go back 3 positions within the container.
    const_iterator operator-=(difference_type step) { 
      if (step >= 0) {
        for (difference_type i = 0; i < step && m_ptr != nullptr; ++i) {
          m_ptr = m_ptr->prev;
        }
      } else {
        for (difference_type i = 0; i > step && m_ptr != nullptr; --i) {
          m_ptr = m_ptr->next;
        }
      }
      return *this;
    }
    /// it->method()
    pointer operator->() const {
      assert(m_ptr != nullptr);
      return m_ptr;
    }

    // We need friendship so the list<T> class may access the m_ptr field.
    friend class list<T>;

    friend std::ostream &operator<<(std::ostream &os_,
                                    const const_iterator &s_) {
      os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
      return os_;
    }
  };

  class iterator : public std::bidirectional_iterator_tag {
    //=== Some aliases to help writing a clearer code.
  public:
    using value_type = T;  //!< The type of the value stored in the list.
    using pointer = T *;   //!< Pointer to the value.
    using reference = T &; //!< reference to the value.
    using const_reference = const T &; //!< const reference to the value.
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

  private:
    Node *m_ptr; //!< The raw pointer.

  public:
    iterator(Node *ptr = nullptr) : m_ptr(ptr) {}
    ~iterator() = default;
    iterator(const iterator &) = default;
    iterator &operator=(const iterator &) = default;
    reference operator*() { return m_ptr->data; }
    const_reference operator*() const { 
      return m_ptr->data;
    }
    iterator operator++() { 
      m_ptr = m_ptr->next;
      return *this;
    }
    iterator operator++(int) { 
      iterator aux = *this;
      ++(*this);
      return aux;
    }
    iterator operator--() { 
      m_ptr = m_ptr->prev;
      return *this;
    }
    iterator operator--(int) { 
      iterator aux = *this;
      --(*this);
      return aux;
    }
    bool operator==(const iterator &rhs) const { 
      return m_ptr == rhs.m_ptr;
    }
    bool operator!=(const iterator &rhs) const { 
      return !(m_ptr == rhs.m_ptr);
    }

    //=== Other methods that you might want to implement.
    /// it += 3; // Go back  3 positions within the container.
    iterator operator+=(difference_type step) { /* TODO */
      if (step >= 0) {
        for (difference_type i = 0; i < step && m_ptr != nullptr; ++i) {
          m_ptr = m_ptr->next;
        }
      } else {
        for (difference_type i = 0; i > step && m_ptr != nullptr; --i) {
          m_ptr = m_ptr->prev;
        }
        return *this;
      }
    }
    /// it -= 3; // Go back  3 positions within the container.
    iterator operator-=(difference_type step) { /* TODO */
      if (step >= 0) {
        for (difference_type i = 0; i < step && m_ptr != nullptr; ++i) {
          m_ptr = m_ptr->prev;
        }
      } else {
        for (difference_type i = 0; i > step && m_ptr != nullptr; --i) {
          m_ptr = m_ptr->next;
        }
      }
      return *this;
    }
    /// it->method()
    pointer operator->() const { /* TODO */
      assert(m_ptr != nullptr);
      return m_ptr;
    }

    // We need friendship so the list<T> class may access the m_ptr field.
    friend class list<T>;

    friend std::ostream &operator<<(std::ostream &os_, const iterator &s_) {
      os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
      return os_;
    }
  };

  //=== Private members.
private:
  size_t m_len; // comprimento da lista.
  Node *m_head; // nó cabeça.
  Node *m_tail; // nó cauda.

public:
  //=== Public interface

  //=== [I] Special members
  /**
  * @brief Construtor que cria uma lista totalmente vazia.
  */
  list() {
    m_head = new Node();
    m_tail = new Node();
    m_head->next = m_tail;
    m_tail->prev = m_head;
    m_len = 0;
  }

  /**
   * @brief Construtor que cria uma lista e a preenche "count" vezes com uma instância padrão de T.
   * @param count Número de instâncias padrões de T que serão inseridas na lista.
   */
  list(size_t count) : list() {
    for (size_t i = 0; i < count; i++) {
      push_back(T{});
    }
  }

  /**
   * @brief Construtor que cria uma lista com os conteúdos do intervalo : [first, last).
   * @param first primeiro elemento do intervalo
   * @param last um elemento após o último elemento do intervalo
   */
  template <typename InputIt> list(InputIt first, InputIt last) : list() {
    for (InputIt it = first; it != last; ++it) {
      push_back(*it);
    }
  }

  /**
   * @brief Construtor cópia.
   * @param clone_ A lista a ser copiada.
   */
  list(const list &clone_) : list() {
    *this = clone_;
  }

  /**
   * @brief Construtor que inicializa a lista a partir de uma lista inicializadora.
   * @param ilist_ A lista inicializadora.
   */
  list(std::initializer_list<T> ilist_)
      : list(ilist_.begin(), ilist_.end()) {}

   /**
   * @brief Destrutor.
   */
  ~list() {
    Node *aux = this->m_head;
    Node *aux2 = nullptr;

    while (aux != nullptr) {
      aux2 = aux;
      aux = aux->next;
      delete aux2;
    }
    this->m_len = 0;
    this->m_head = nullptr;
    this->m_tail = nullptr;
  }

  /**
 * @brief Sobrecarga do operador de atribuição (=) para copiar o conteúdo de outra lista.
 * @param rhs A lista a ser copiada.
 * @return Uma referência para a lista atualizada.
 */
  list &operator=(const list &rhs) { 
    if (&rhs == this) { // Teste para evitar autoatribuição ou `l1 = l1;`
      return *this;
    }
    if (not empty()) { // Limpar lista antes de preencher c/ novos valores.
      clear();
    }
    // std::copy(rhs.begin(),rhs.end(), this->begin())
    Node *current = rhs.m_head->next;
    // Não há ponteiro sendo compartilhado, esta operação aloca memória
    while (current != rhs.m_tail) {
      this->push_back(current->data);
      current = current->next;
    }
    this->m_len = rhs.m_len;
    return *this;
  }

  /**
  * @brief Sobrecarga do operador de atribuição (=) para atribuir os elementos de uma lista inicializadora.
  * @param ilist_ A lista inicializadora contendo os elementos a serem atribuídos.
  * @return Uma referência para a lista atualizada. 
  * */
  list &operator=(std::initializer_list<T> ilist_) { /* TODO */
    if (not empty()) { // Limpar lista antes de preencher c/ novos valores.
      clear();
    }
    // Inserir na lista cada um dos elementos do ilist_
    for(const auto e : ilist_){
      push_back(e);
    }
    return *this;
  }


  //=== [II] ITERATORS


  /**
 * @brief Obtém um iterador para o primeiro elemento da lista.
 * @return Um iterador apontando para o primeiro elemento da lista.
  */
  iterator begin() { return iterator(m_head->next); }

  /**
 * @brief Obtém um iterador constante para o primeiro elemento da lista.
 * @return Um iterador constante apontando para o primeiro elemento da lista.
  */
  const_iterator cbegin() const { return const_iterator(m_head->next); }

  /**
 * @brief Obtém um iterador para o final da lista.
 * @return Um iterador apontando para o final da lista.
 */
  iterator end() { return iterator(m_tail); }

  /**
 * @brief Obtém um iterador constante para o final da lista.
 * @return Um iterador constante apontando para o final da lista.
 */
  const_iterator cend() const { return const_iterator(m_tail); }



  //=== [III] Capacity/Status


/**
 * @brief Verifica se a lista está vazia.
 * @return true se a lista estiver vazia, false caso contrário.
 */
  [[nodiscard]] bool empty() const { return m_len == 0; }

  /**
 * @brief Obtém o tamanho atual da lista.
 * @return O número de elementos (nodes) na lista.
 */
  [[nodiscard]] size_t size() const { return m_len; }


  //=== [IV] Modifiers

/**
* @brief Remove todos os elementos da lista 
*/
  void clear() {
    if (empty()) {
      return;
    }
    Node *current = m_head->next;
    Node *prev = current->prev;
    while (current != m_tail) {
      prev = current;
      current = current->next;
      delete prev;
    }
    m_len = 0;
    m_head->next = m_tail;
    m_tail->prev = m_head;
  }

/**
 * @brief Obtém o primeiro elemento da lista.
 * @return Uma referência constante para o primeiro elemento da lista.
 * @throw std::length_error se a lista estiver vazia.
 */
  T front() {
    if (empty()) throw std::length_error("Container is empty");
    return m_head->next->data;
  }

  /**
 * @brief Obtém o primeiro elemento da lista (versão constante).
 * @return Uma referência constante para o primeiro elemento da lista.
 * @throw std::length_error se a lista estiver vazia.
 */
  T front() const {
    if (empty()) throw std::length_error("Container is empty");
    return m_head->next->data;
  }

/**
 * @brief Obtém o último elemento da lista.
 * @return Uma referência para o último elemento da lista.
 * @throw std::length_error se a lista estiver vazia.
 */
  T back() {
    if (empty()) throw std::length_error("Container is empty");
    return m_tail->prev->data;
  }

/**
 * @brief Obtém o último elemento da lista (versão constante).
 * @return Uma referência para o último elemento da lista.
 * @throw std::length_error se a lista estiver vazia.
 */
  T back() const {
    if (empty()) throw std::length_error("Container is empty");
    return m_tail->prev->data;
  }

  /**
 * @brief Insere um elemento no início da lista.
 * @param value_ O valor do elemento a ser inserido.
 */
  void push_front(const T &value_) {
    // Passo (1): criar novo nó.
    Node *new_node = new Node();
    new_node->data = value_;
    // Ptr auxiliar para facilitar o entendimento.
    Node *current_first = m_head->next; // Aponta para o atual primeiro.
    // Passo (2): novo nó se conecta na lista.
    new_node->prev = m_head;
    new_node->next = current_first;
    // Passo (3): a lista reconhece o novo nó como parte dela.
    current_first->prev = new_node;
    m_head->next = new_node;
    // Aumento da contagem
    m_len++;
  }

  /**
 * @brief Imprime os elementos da lista.
 */
  void print_list() {
    Node *aux = m_head->next;
    for (int i = 0; i < m_len; i++) {
      std::cout << aux->data << " ";
      aux = aux->next;
    }
  }

  /**
 * @brief Insere um elemento no final da lista.
 * @param value O valor do elemento a ser inserido.
 */
  void push_back(const T &value) {
    // Passo (1): criar novo nó.
    Node *new_node = new Node();
    new_node->data = value;
    // Ptr auxiliar para facilitar o entendimento.
    Node *current_last = m_tail->prev; // Aponta para o atual último.
    // Passo (2): novo nó se conecta na lista.
    new_node->next = m_tail;
    new_node->prev = current_last;
    // Passo (3): a lista reconhece o novo nó como parte dela.
    current_last->next = new_node;
    m_tail->prev = new_node;
    // Aumento da contagem
    m_len++;
  }

  /**
 * @brief Remove o primeiro elemento da lista.
 */
  void pop_front() {
    if (empty())
      return;
    Node *aux = m_head->next;
    m_head->next = aux->next;
    aux->next->prev = m_head;
    delete aux;
    m_len--;
  }

/**
 * @brief Remove o último elemento da lista.
 */
  void pop_back() {
    if (empty())
      return;
    Node *aux = m_tail->prev;
    m_tail->prev = aux->prev;
    aux->prev->next = m_tail;
    delete aux;
    m_len--;
  }

  //=== [IV-a] MODIFIERS W/ ITERATORS

  /**
 * @brief Limpa a lista e atribui novos elementos a partir de um intervalo.
 * @param first_ Um iterador para o primeiro elemento do intervalo.
 * @param last_ Um iterador para o elemento após o último do intervalo.
 */
  template <class InItr> void assign(InItr first_, InItr last_) {
    clear(); 
    for (InItr itr = first_; itr != last_; ++itr) {
        push_back(*itr); 
    }
  }

  /**
 * @brief Limpa a lista e atribui novos elementos a partir de uma lista inicializadora.
 * @param ilist_ Lista inicializadora
 */
  void assign(std::initializer_list<T> ilist_) {
    clear(); 
    for (const T& value : ilist_) {
        push_back(value); 
    }
  }

  /**
  * @brief Insere um novo valor na lista antes do iterador 'it' e retorna um iterador para o novo nó.
  * @param pos_ Um iterador para a posição antes da qual desejamos inserir os dados. 
  * @param value_ O valor que desejamos inserir na lista. 
  * @return Um iterador para o novo elemento na lista.
  */
  iterator insert(iterator pos_, const T &value_) {
    // Passo (1): criar novo nó.
    Node *new_node = new Node();
    new_node->data = value_;
    // Passo (2): novo nó se conecta na lista.
    new_node->prev = pos_.m_ptr->prev;
    new_node->next = pos_.m_ptr;
    // Passo (3): a lista reconhece o novo nó como parte dela.
    pos_.m_ptr->prev->next = new_node;
    pos_.m_ptr->prev = new_node;
    // Aumento da contagem
    m_len++;
    // Retorna um iterador para a posição em que new_node foi inserido
    return iterator(new_node);
  }

  /**
 *@brief Insere elementos de um intervalo na lista antes da posição indicada pelo iterador 'pos_'.
 * @param pos_ O iterador para a posição antes da qual queremos inserir os dados.
 * @param first_ O iterador para o primeiro elemento do intervalo.
 * @param last_ O iterador para o elemento após o último do intervalo.
 * @return Um iterador para o novo elemento inserido na lista.
*/
  template <typename InItr>
  iterator insert(iterator pos_, InItr first_, InItr last_) { 
    for (InItr it = first_; it != last_; ++it) {
        pos_ = insert(pos_, *it);
        ++pos_;
    }
    return iterator(pos_);
  }

/**
 * @brief Insere elementos de uma lista inicializadora na lista antes da posição indicada pelo iterador 'pos_'.
 * @param pos_ O iterador para a posição antes da qual queremos inserir os dados.
 * @param ilist A lista inicializadora contendo os elementos a serem inseridos.
 * @return Um iterador para o novo elemento inserido na lista.
*/
  iterator insert(iterator pos_, std::initializer_list<T> ilist) {
    for (const T& value : ilist) {
       pos_ = insert(pos_, value);
        ++pos_;
    }
    return pos_;
}

  /**
   * @brief  Apaga o nó apontado por 'it_' e retorna um iterador para o
nó imediatamente após o nó excluído.
   *
   *  @param it_ O nó que desejamos excluir.
   *  @return Um iterador para o nó seguinte ao nó excluído.
   */
  iterator erase(iterator pos) {
    Node* current = pos.m_ptr;
    Node* next_node = current->next;
    Node* prev_node = current->prev;

    if (prev_node != nullptr) {
        prev_node->next = next_node;
    } else {
        m_head = next_node;
    }

    if (next_node != nullptr) {
        next_node->prev = prev_node;
    } else {
        m_tail = prev_node;
    }

    delete current;
    m_len--;
  
    return iterator(next_node);
}
  
  /**
  * @brief Remove os elementos no intervalo [first, last) da lista.
  * @param first Um iterador para o primeiro elemento a ser removido.
  * @param last Um iterador para o elemento seguinte ao último a ser removido.
  * @return Um iterador apontando para o elemento seguinte ao último removido.
  */
  iterator erase(iterator first, iterator last) {
    Node* prev_node = first.m_ptr->prev;
    Node* next_node = last.m_ptr;

    if (prev_node != nullptr) {
        prev_node->next = next_node;
    } else {
        m_head = next_node;
    }

    if (next_node != nullptr) {
        next_node->prev = prev_node;
    } else {
        m_tail = prev_node;
    }

    for (Node* current = first.m_ptr; current != next_node;) {
        Node* next = current->next;
        delete current;
        current = next;
        m_len--;
    }

    return iterator(next_node);
}

  //=== [V] UTILITY METHODS
  void merge(list &other) {}

  /**
  * @brief Move os elementos da lista 'other' para a posição 'pos' na lista atual. Os elementos são removidos da lista 'other' e inseridos na lista atual
antes da posição indicada por 'pos'.
  * @param pos Um iterador para a posição na lista atual onde os elementos serão inseridos.
  * @param other A lista de onde os elementos serão movidos.
*/

  void splice(const_iterator pos, list& other) {
    if (other.empty()) {
        return; // Quando other é vazio nada acontece
    }

    // ajusta os ponteiros
    other.m_head->next->prev = pos.m_ptr->prev;
    pos.m_ptr->prev->next = other.m_head->next;

    other.m_tail->prev->next = pos.m_ptr;
    pos.m_ptr->prev = other.m_tail->prev;

    // ajusta o tamanho
    m_len += other.m_len;
    other.m_len = 0;

    // Reseta a lista other
    other.m_head->next = other.m_tail;
    other.m_tail->prev = other.m_head;
}

  /** 
  * @brief Inverte a ordem dos elementos na lista. A função reverte a ordem dos elementos na lista atual. Se a lista contiver menos de 2 elementos, não ocorre nenhuma alteração.
*/
  void reverse() {
    if(this->m_len <= 1)
      return;

    Node* ptr1 = this->m_head->next;
    Node* ptr2 = this->m_head->next->next;
    Node* aux = ptr1;

    ptr1->next = m_head;
    ptr1->prev = ptr2;

    while(ptr2 != this->m_tail){
      ptr2->prev = ptr2->next;
      ptr2->next = ptr1;
      ptr1 = ptr2;
      ptr2 = ptr2->prev;
    }

    this->m_head->next = ptr1;
    ptr1->prev = this->m_head;

    this->m_tail->prev = aux;
    aux->next = this->m_tail;
 
  }

  /**
  * @brief Remove elementos duplicados da lista. A função percorre a lista e remove elementos duplicados consecutivos, mantendo apenas uma ocorrência de cada valor. Se a lista estiver vazia ou contiver apenas um elemento, não ocorre nenhuma alteração.
*/
  void unique() {
    if (empty()) {
        return; // Nenhum elemento na lista, nada para fazer
    }
    auto current = m_head->next; // Começa no primeiro elemento
    while (current->next != m_tail) {
        if (current->data == current->next->data) { //Checa se dois elementos consecutivos são iguais
            //Remove o elemento duplicado depois do current.
            erase(current->next);
        } else {
            current = current->next; // Vai para o próximo elemento
        }
    }
}

 void sort() {
    if (m_len <= 1) {
      return; // Não há nada para ordenar
    }

    bool swapped;
    do {
      swapped = false;
      Node *current = m_head->next;
      while (current->next != m_tail) {
        if (current->data > current->next->data) {
          T temp = current->data;
          current->data = current->next->data;
          current->next->data = temp;
          swapped = true;
        }
        current = current->next;
      }
    } while (swapped);
  }
};

// FIM DA CLASSE LISTA
 
//=== [VI] OPERATORS

/**
*
* @brief Sobrecarga do operador de igualdade (==) para comparar duas listas. Compara se duas listas são iguais, verificando se possuem o mesmo tamanho e se seus elementos correspondentes são iguais.
*
* @param l1_ A primeira lista a ser comparada.
* @param l2_ A segunda lista a ser comparada.
*
* @return true se as listas são iguais, false caso contrário.
*/
  template <typename T>
  inline bool operator==( const sc::list<T> &l1_, const sc::list<T> &l2_) {
    if (l1_.size() != l2_.size()) {
      return false; //Tamanhos diferentes significa que as listas não são iguais.
    }

    auto it1 = l1_.cbegin();
    auto it2 = l2_.cbegin();

    while (!(it1 == l1_.cend()) && !(it2 == l2_.cend())) {
      if (!(*it1 == *it2)) {
        return false; // Valores correspondentes não são iguais
      }
      //para se mover nas listas
      ++it1;
      ++it2;
    }

    return true; // todos os elementos são iguais
  }


/**
* @brief Sobrecarga do operador de desigualdade (!=) para comparar duas listas. Compara se duas listas são diferentes, verificando se são iguais utilizando o operador de igualdade (==) e negando o resultado.
* @param l1_ A primeira lista a ser comparada.
* @param l2_ A segunda lista a ser comparada.
* @return true se as listas são diferentes, false caso contrário.
*/
template <typename T>
inline bool operator!=(const sc::list<T> &l1_, const sc::list<T> &l2_) {
 return !(l1_ == l2_);
} 

}
#endif