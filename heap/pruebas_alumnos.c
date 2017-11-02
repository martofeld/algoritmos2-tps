//
// Created by Martin Feldsztejn on 11/2/17.
//

#include "../testing.c"
#include "heap.h"

int comparar_ints(int a, int b){
    if (a == b){
        return 0;
    }
    if (a < b){
        return 1;
    }
    return -1;
}

int comparar_void(const void* a, const void* b){
    return comparar_ints((int) a, (int) b);
}

void pruebas_encolar(){
    heap_t* heap = heap_crear(comparar_void);
    int array[] = {0,1,2,3,4,5,6,7,8};
    heap_encolar(heap, &array[4]);
    heap_encolar(heap, &array[2]);
    heap_encolar(heap, &array[7]);
    heap_encolar(heap, &array[5]);
    heap_encolar(heap, &array[6]);
    heap_encolar(heap, &array[8]);
    heap_encolar(heap, &array[0]);
    print_test("La cantidad es 7", heap_cantidad(heap) == 7);
    heap_destruir(heap, NULL);
}

void pruebas_desencolar(){
    heap_t* heap = heap_crear(comparar_void);
    int array[] = {0,1,2,3,4,5,6,7,8};
    heap_encolar(heap, &array[4]);
    heap_encolar(heap, &array[2]);
    heap_encolar(heap, &array[7]);
    heap_encolar(heap, &array[5]);
    heap_encolar(heap, &array[6]);
    heap_encolar(heap, &array[8]);
    heap_encolar(heap, &array[0]);
    print_test("La cantidad es 7", heap_cantidad(heap) == 7);
    print_test("Desncolar deberia dar 8", heap_desencolar(heap) == &array[8]);
    heap_destruir(heap, NULL);
}

void pruebas(){
    pruebas_encolar();
    pruebas_desencolar();
}

int main(){
    pruebas();
    return 0;
}