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


void pruebas_volumen_heap(void){
    heap_t* heap= heap_crear(comparar_void);
    int arreglo[VOLUMEN];
    bool OK=true;

//Aumentamos en cantidad el volumen de la heap
    for(int i=0; i<VOLUMEN; i++){
        arreglo[i]=i;
        OK&=heap_encolar(heap,&arreglo[i]);
    }   

    print_test("Hace crecer el heap",OK);

    print_test("El heap no esta vacio",!heap_esta_vacio(heap));
    print_test("El largo del heap es 500",heap_cantidad(heap)==VOLUMEN);

//Vaciamos la heap

    for(int i=0; i<VOLUMEN; i++){
        heap_desencolar(heap);
    }

    print_test("El heap esta vacio",heap_esta_vacio(heap));

//La heap vaciada se comporta como recien creada

    print_test("Largo del heap es 0", !heap_cantidad(heap));
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}


void pruebas(){
    pruebas_encolar();
    pruebas_desencolar();
}

int main(){
    pruebas();
    return 0;
}