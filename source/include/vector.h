#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>        // std::copy, std::equal, std::fill
#include <cassert>          // assert()
#include <cstddef>          // std::size_t
#include <exception>        // std::out_of_range
#include <initializer_list> // std::initializer_list
#include <iostream>         // std::cout, std::endl
#include <iterator> // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <limits> // std::numeric_limits<T>
#include <memory> // std::unique_ptr

/// Sequence container namespace.
namespace sc {
/// Implements tha infrastrcture to support a bidirectional iterator.
template <class T> class MyForwardIterator {
public:
  using iterator = MyForwardIterator; //!< Alias to iterator.
  // Below we have the iterator_traits common interface
  typedef std::ptrdiff_t difference_type;  //!< Difference type used to calculated distance between
                        //!< iterators.
  typedef T value_type; //!< Value type the iterator points to.
  typedef T *pointer;   //!< Pointer to the value type.
  typedef T &reference; //!< Reference to the value type.
  typedef const T &const_reference; //!< Reference to the value type.
  typedef std::bidirectional_iterator_tag
      iterator_category; //!< Iterator category.

  /*! Create an iterator around a raw pointer.
   * \param pt_ raw pointer to the container.
   */
  MyForwardIterator(pointer pt = nullptr) : m_ptr(pt) { /* empty */
  }

  /// Access the content the iterator points to.
  reference operator*(void) const {
    assert(m_ptr != nullptr);
    return *m_ptr;
  }

  /// Overloaded `->` operator.
  pointer operator->(void) const {
    assert(m_ptr != nullptr);
    return m_ptr;
  }

  /// Assignment operator.
  iterator &operator=(const iterator& other) = default;

  /// Copy constructor.
  MyForwardIterator(const iterator& other) = default;

  /// Pre-increment operator.
  iterator operator++(void) {
    m_ptr++;
    return *this;
  }

  /// Post-increment operator.
  iterator operator++(int) {
    iterator original = *this;
    ++(*this);
    return original;
  }

  /// Pre-decrement operator.
  iterator operator--(void) {
    m_ptr--;
    return *this;
  }

  /// Post-decrement operator.
  iterator operator--(int) {
    iterator original = *this;
    --(*this);
    return original;
  }

  iterator &operator+=(difference_type offset) {
    iterator &it{*this};
    for(difference_type i=0; i<offset; ++i){
      ++it;
    }
    return it;
  }
  
  iterator &operator-=(difference_type offset) {
    iterator &it{*this};
     for(difference_type i=0; i<offset; ++i){
      --it;
    }
    return it;
  }

  friend bool operator<(const iterator &ita, const iterator &itb) {
    if(ita.m_ptr < itb.m_ptr) return true;
    return false;
  }

  friend bool operator>(const iterator &ita, const iterator &itb) {
    if(ita.m_ptr > itb.m_ptr) return true;
    return false;
  }
  friend bool operator>=(const iterator &ita, const iterator &itb) {
    if(ita.m_ptr >= itb.m_ptr) return true;
    return false;
  }

  friend bool operator<=(const iterator &ita, const iterator &itb) {
    if(ita.m_ptr <= itb.m_ptr) return true;
    return false;
  }

  friend iterator operator+(difference_type offset, iterator it) {
    for(difference_type i=0; i<offset; ++i){
      ++it;
    }
    return it;
  }

  friend iterator operator+(iterator it, difference_type offset) {
    for(difference_type i=0; i<offset; ++i){
      ++it;
    }
    return it;
  }

  friend iterator operator-(iterator it, difference_type offset) {
    for(difference_type i=0; i<offset; ++i){
      --it;
    }
    return it;
  }

  /// Equality operator.
  bool operator==(const iterator &rhs_) const {
    if(m_ptr == rhs_.m_ptr) return true;
    return false;
  }

  /// Not equality operator.
  bool operator!=(const iterator &rhs_) const {
    if(m_ptr == rhs_.m_ptr) return false;
    return true;
  }

  /// Returns the difference between two iterators.
  difference_type operator-(const iterator &rhs_) const {
    difference_type dif = m_ptr - rhs_.m_ptr;
    return dif;
  }

  /// Stream extractor operator.
  friend std::ostream &operator<<(std::ostream &os_,
                                  const MyForwardIterator &p_) {
    os_ << "[@ " << p_.m_ptr << ": " << *p_.m_ptr << " ]";
    return os_;
  }

private:
  pointer m_ptr; //!< The raw pointer.
};






/// This class implements the ADT list with dynamic array.
/*!
 * sc::vector is a sequence container that encapsulates dynamic size arrays.
 *
 * The elements are stored contiguously, which means that elements can
 * be accessed not only through iterators, but also using offsets to
 * regular pointers to elements.
 * This means that a pointer to an element of a vector may be passed to
 * any function that expects a pointer to an element of an array.
 *
 * \tparam T The type of the elements.
 */
template <typename T> class vector {
  //=== Aliases
public:
  using size_type = unsigned long; //!< The size type.
  using value_type = T;            //!< The value type.
  using pointer = value_type *; //!< Pointer to a value stored in the container.
  using reference =
      value_type &; //!< Reference to a value stored in the container.
  using const_reference = const value_type &; //!< Const reference to a value
                                              //!< stored in the container.

  using iterator =
      MyForwardIterator<value_type>; //!< The iterator, instantiated from a
                                     //!< template class.
  using const_iterator =
      MyForwardIterator<const value_type>; //!< The const_iterator,
                                           //!< instantiated from a template
                                           //!< class.

public:
  //=== [I] SPECIAL MEMBERS (6 OF THEM)

/**
* @brief construtor padrão
* @param recebe inteiro e, com esse dado, aloca o espaço na memório para o m_storage, o m_capacity; o m_end começa em zero.
* @return void.
*/
  explicit vector(size_type cp = 0) {
    m_storage = new T[cp];
    m_capacity = cp;
    m_end = cp; 
  }

//Destrutor
  virtual ~vector(void) {
    if (m_storage)
      delete[] m_storage;
  }

/**
* @brief cópia padrão
* @param recebe o endereço de memório do objeto a ser copiado
* @return void.
*/
    vector(const vector& original) : 
      m_capacity(original.m_capacity),
      m_end(original.m_end),
      m_storage(new T[original.m_capacity])
{
      for(int i=0;i<original.m_capacity;i++){
        this->m_storage[i] = original.m_storage[i];
      }


}//fim do vector cópia

  vector(const std::initializer_list<T> &il) {
    m_capacity = il.size();
    m_storage = new T[m_capacity];
    m_end = m_capacity; // Array começa cheio.
    // Copy the elements from the il into the array.
    std::copy(il.begin(), il.end(), m_storage);
  }

vector &operator=(const vector &other){
   if (this == &other) return *this;
  
  delete[] m_storage;
  
  m_capacity = other.m_capacity;
  m_storage = new T[m_capacity];
  m_end = other.m_end;
  
  for (size_type i = 0; i < m_end; i++) {
    m_storage[i] = other.m_storage[i];
  }
  
  return *this;
}

  //=== [II] ITERATORS
  iterator begin(void) { return iterator(&m_storage[0]); }
    
    
  iterator end(void) { return iterator(&m_storage[0] + m_end); }
    
  const_iterator cbegin(void) const { return const_iterator(&m_storage[0]); }
    
  const_iterator cend(void) const { return const_iterator(&m_storage[0] + m_end); }

  // [III] Capacity
  size_type size(void) const { return m_end; }
  
  size_type capacity(void) const { return m_capacity; }
    
  bool empty(void) const {
    if(m_end == 0) return true;
    return false;
   }

  // [IV] Modifiers
  void clear(void){ m_end = 0; }

  void push_back(const_reference data){
    if(full()){
      T *new_m_storage = new T[++m_capacity];
      for(size_type i=0; i<m_end; i++){
        new_m_storage[i] = m_storage[i];
      }
      m_storage = new_m_storage;
    }
    m_storage[m_end++] = data;
  }

  void pop_back(void){
    if (empty()) {
      throw std::length_error("Vector está vazio!");
    }
    m_end--;
  }

  void pop_front(void){
    if (empty()) {
      throw std::length_error("Vector está vazio!");
    }
    for (size_type i = 1; i < m_end; ++i) {
        m_storage[i - 1] = m_storage[i];
    }
    --m_end;
  }


void reserve(size_type qtd);

  iterator insert(iterator pos_, const_reference value_){
      size_type index = pos_ - this->begin();
      this->push_back(value_);
      std::rotate(this->begin() + index, this->end() - 1, this->end());
      return this->begin() + index;
  }

  iterator insert(const_iterator pos_, const_reference value_){
      size_type index = pos_ - this->begin();
      this->push_back(value_);
      std::rotate(this->begin() + index, this->end() - 1, this->end());
      return this->begin() + index;
  }

  template <typename InputItr>
  iterator insert(iterator pos_, InputItr first_, InputItr last_);
  template <typename InputItr>
  iterator insert(const_iterator pos_, InputItr first_, InputItr last_);

  iterator insert(iterator pos_, const std::initializer_list<value_type> &ilist_);
  iterator insert(const_iterator pos_, const std::initializer_list<value_type> &ilist_);

  void shrink_to_fit(void);

  void assign(size_type count_, const_reference value_){
      this->clear();
      this->insert(this->begin(), count_, value_);
  }
  
  void assign(const std::initializer_list<T> &ilist);
  template <typename InputItr> void assign(InputItr first, InputItr last);

  iterator erase(iterator first, iterator last){
    size_type range = std::distance(first, last);
    iterator result = first;

    for (iterator it = last; it != end(); ++it, ++result) {
        *result = std::move(*it);
    }
    for (size_type i = 0; i < range; ++i) {
        pop_back();
    }
    return first;
  }

  iterator erase(const_iterator first, const_iterator last){
    size_type range = std::distance(first, last);
    iterator result = first;

    for (iterator it = last; it != end(); ++it, ++result) {
        *result = std::move(*it);
    }
    for (size_type i = 0; i < range; ++i) {
        pop_back();
    }
    return first;
  }

  iterator erase(const_iterator pos){
    std::destroy_at(&*pos);

    for (iterator it = pos + 1; it != end(); ++it) {
        *(it - 1) = std::move(*it);
    }

    --m_end;

    return pos;
  }

  iterator erase(iterator pos){
    std::destroy_at(&*pos);

    for (iterator it = pos + 1; it != end(); ++it) {
        *(it - 1) = std::move(*it);
    }

    --m_end;

    return pos;
  }

  // [V] Element access
  const_reference back(void) const {
    return m_storage[m_end - 1]; 
  }
                      
  const_reference front(void) const { return m_storage[0]; }
                      
  reference back(void) { return m_storage[m_end - 1]; }
                      
  reference front(void) { return m_storage[0]; }
                      
  const_reference operator[](size_type idx) const { return m_storage[idx]; }
                      
  reference operator[](size_type idx) { return m_storage[idx]; }
                      
  const_reference at(size_type idx) const{
    if(idx >= m_end) throw std::out_of_range("Posição passada é inválida para o vector");
    return m_storage[idx];
  }

  reference at(size_type idx){
    if(idx >= m_end) throw std::out_of_range("Posição passada é inválida para o vector");
    return m_storage[idx];
  }


  // [VII] Friend functions.
  friend std::ostream &operator<<(std::ostream &os_, const vector<T> &v_) {
    // O que eu quero imprimir???
    os_ << "{ ";
    for (auto i{0u}; i < v_.m_capacity; ++i) {
      if (i == v_.m_end)
        os_ << "| ";
      os_ << v_.m_storage[i] << " ";
    }
    os_ << "}, m_end=" << v_.m_end << ", m_capacity=" << v_.m_capacity;

    return os_;
  } 

  friend void swap(vector<T> &first_, vector<T> &second_) {
    // enable ADL
    using std::swap;

    // Swap each member of the class.
    swap(first_.m_end, second_.m_end);
    swap(first_.m_capacity, second_.m_capacity);
    swap(first_.m_storage, second_.m_storage);
  }

private:
  bool full(void) const { 
    if(m_capacity == m_end) return true;
    return false;
    }

  size_type m_end; //!< The list's current size (or index past-last valid element).
  size_type m_capacity; //!< The list's storage capacity.
  T *m_storage;         //!< The list's data storage area.
};

// [VI] Operators
template <typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
    return !(lhs == rhs);
}

}

#endif
