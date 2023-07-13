#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <sstream>
using std::ostringstream;
#include <iterator>
using std::next;
using std::ostream_iterator;
#include <functional>
using std::function;
using std::less;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <algorithm>
using std::copy;
using std::for_each;
using std::max_element;
#include <cmath>
using std::pow;
#include <string>
using std::string;
using std::to_string;
#include <ctime>

using value_type = int;

namespace sa { // sa = sorting algorithms

template <typename DataType, typename Compare>
void insertion(DataType *first, DataType *last, Compare cmp){
  int i, j;
  int tamanho = last - first;
  DataType aux;

  for(i = 0; i < tamanho; i++){
    aux = first[i];
    j = i - 1;

    while( (j >= 0) && ( cmp(aux,first[j]) )){
      first[j + 1] = first[j];
      j--;
    }
    first[j + 1] = aux;
  }
}

template <typename DataType, typename Compare>
void selection(DataType *first, DataType *last, Compare cmp){
  last = last - 1;
  DataType *i, *j, *min;

    for(i = first; i < last; i++){
        min=i;

        for(j=i+1; j<=last; j++){
            if(cmp(*j, *min)){
                min = j;
            }
        }
        if(min != i){
            DataType aux = *i;
            *i = *min;
            *min = aux;
        }
    }
}

template <typename DataType, typename Compare>
void bubble(DataType *first, DataType *last, Compare cmp){
  int indice = (last - first) - 1;
  int continua = 1; 
  DataType aux;

    while(continua){
        continua = 0;

        for(int i=0; i<indice; i++){

            if(cmp(first[i+1], first[i])){
                aux = first[i];
                first[i] = first[i+1];
                first[i+1] = aux;
                continua = 1;
            }
        }
        indice--;
    }
}

template <typename DataType, typename Compare>
void shell(DataType *first, DataType *last, Compare cmp){
  int tamanho = last - first; 
  int gap = tamanho / 2;

    while (gap > 0) {

        for (int i = gap; i < tamanho; i++) {
            int j = i;
            DataType aux = first[i];

            while (j >= gap && cmp(aux, first[j - gap])) {
                first[j] = first[j - gap];
                j -= gap;
            }   

            first[j] = aux;
        }

        gap /= 2;
    }
}

template <typename DataType, typename Compare>
void merge(DataType* first, DataType* middle, DataType* last, Compare cmp) {
    std::ptrdiff_t size1 = middle - first;
    std::ptrdiff_t size2 = last - middle;

    std::unique_ptr<DataType[]> left(new DataType[size1]);
    std::unique_ptr<DataType[]> right(new DataType[size2]);

    std::copy(first, middle, left.get());
    std::copy(middle, last, right.get());

    DataType* left_ptr = left.get();
    DataType* right_ptr = right.get();

    while (left_ptr < left.get() + size1 && right_ptr < right.get() + size2) {
        if (cmp(*right_ptr, *left_ptr)) {
            *first++ = std::move(*right_ptr++);
        } else {
            *first++ = std::move(*left_ptr++);
        }
    }

    while (left_ptr < left.get() + size1) {
        *first++ = std::move(*left_ptr++);
    }

    while (right_ptr < right.get() + size2) {
        *first++ = std::move(*right_ptr++);
    }
}

template <typename DataType, typename Compare>
void merge_sort(DataType* first, DataType* last, Compare cmp) {
    std::ptrdiff_t size = last - first;
    if (size > 1) {
        DataType* middle = first + size / 2;
        merge_sort(first, middle, cmp);
        merge_sort(middle, last, cmp);
        merge(first, middle, last, cmp);
    }
}

template <typename DataType, typename Compare>
DataType* partition(DataType *first, DataType *last, DataType *pivot, Compare comp){
    DataType *slow = first;
    DataType *fast = first;

    while(fast != pivot){

        if(comp(*fast, *pivot)){
            std::iter_swap(slow, fast);
            slow++;
        } 
        fast++;
    }

    std::iter_swap(slow, pivot);
    return slow;  
}

template <typename DataType, typename Compare>
void quick(DataType *first, DataType *last, Compare comp){
    int tamanho = last - first;
    if (tamanho > 1) {
        DataType* pivot = partition<DataType>(first, last, last - 1, comp);
        quick(first, pivot, comp);
        quick(pivot + 1, last, comp);
    }
}

template <typename DataType, typename Comparator>
void radix(DataType *first, DataType *last, Comparator cmp){
    int tamanho = last - first;

    DataType max = first[0];
    for (int i = 1; i < tamanho; i++) {
        if (cmp(max, first[i])) max = first[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10){

        const int RANGE = 10; 
        DataType output[tamanho];
        DataType count[RANGE] = {0};

    for (int i = 0; i < tamanho; i++)
        count[(first[i] / exp) % 10]++;

    for (int i = 1; i < RANGE; i++)
        count[i] += count[i - 1];

    for (int i = tamanho - 1; i >= 0; i--) {
        output[count[(first[i] / exp) % 10] - 1] = first[i];
        count[(first[i] / exp) % 10]--;
    }

    for (int i = 0; i < tamanho; i++)
        first[i] = output[i];
    }
}

}; // namespace sa
#endif // ORDENACAO_H



