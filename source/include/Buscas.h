#ifndef BUSCAS_H
#define BUSCAS_H

using value_type = int;

namespace sa {

    value_type * bsearch( value_type * first, value_type * last, value_type value ){
        int count = last - first;

        while(count != 0){
            int step = count/2;
            int* mid = first + step; // salta para o meio!

            if(*mid == value) //first[count/2] = target
                return mid;
            else if(value < *mid){ //ir para esquerda
                count = step;
            }
            else{ //ir para direita
                first = mid + 1;
                count = count - (step + 1);
            }
        }
        return last;
    }

    value_type * rbsearch( value_type * first, value_type * last, value_type value ){
        if (first > last) return last + 1;  // não encontrou o elemento

        int *mid = first + (last - first) / 2;

        if (*mid == value)  return mid;  // encontrou o elemento
         
        else if (*mid > value) return rbsearch(first, mid - 1, value); // busca na metade esquerda
        else return rbsearch(mid + 1, last, value);  // busca na metade direita
    }
}

#endif


