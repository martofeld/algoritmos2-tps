//
// Created by Martin Feldsztejn on 11/2/17.
//

#include "../testing.c"
#include "heap.h"
#define VOLUMEN 500

int comparar_ints(int *a, int *b) {
    if (*a == *b) {
        return 0;
    }
    if (*a < *b) {
        return 1;
    }
    return -1;
}

int comparar_void(const void *a, const void *b) {
    return comparar_ints((int *) a, (int *) b);
}

void pruebas_encolar() {
    heap_t *heap = heap_crear(comparar_void);
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    heap_encolar(heap, &array[4]);
    heap_encolar(heap, &array[2]);
    heap_encolar(heap, &array[7]);
    heap_encolar(heap, &array[5]);
    heap_encolar(heap, &array[6]);
    heap_encolar(heap, &array[8]);
    heap_encolar(heap, &array[0]);
    print_test("La cantidad es 7", heap_cantidad(heap) == 7);
    print_test("El maximo es 8", heap_ver_max(heap) == &array[8]);
    heap_destruir(heap, NULL);
}

void pruebas_desencolar() {
    heap_t *heap = heap_crear(comparar_void);
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    heap_encolar(heap, &array[4]);
    heap_encolar(heap, &array[2]);
    heap_encolar(heap, &array[7]);
    heap_encolar(heap, &array[5]);
    heap_encolar(heap, &array[6]);
    heap_encolar(heap, &array[8]);
    heap_encolar(heap, &array[0]);
    print_test("La cantidad es 7", heap_cantidad(heap) == 7);
    print_test("Desencolar deberia dar 8", heap_desencolar(heap) == &array[8]);
    print_test("Desencolar deberia dar 7", heap_desencolar(heap) == &array[7]);
    print_test("Desencolar deberia dar 6", heap_desencolar(heap) == &array[6]);
    print_test("Desencolar deberia dar 5", heap_desencolar(heap) == &array[5]);
    print_test("Desencolar deberia dar 4", heap_desencolar(heap) == &array[4]);
    print_test("Desencolar deberia dar 3", heap_desencolar(heap) == &array[2]);
    print_test("Desencolar deberia dar 2", heap_desencolar(heap) == &array[0]);
    print_test("El heap deberia estar vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

void pruebas_heapify() {
    int array[] = {5, 2, 7, 3, 8, 1, 0, 9};
    size_t largo = sizeof(array) / sizeof(int);
    void *auxArray[largo];
    for (int i = 0; i < largo; i++) {
        auxArray[i] = &array[i];
    }
    heap_t *heap = heap_crear_arr(auxArray, largo, comparar_void);

    print_test("El maximo es 9", heap_ver_max(heap) == &array[7]);
    print_test("El maximo es 9", heap_desencolar(heap) == &array[7]);
    print_test("El maximo es 8", heap_desencolar(heap) == &array[4]);
    print_test("El maximo es 7", heap_desencolar(heap) == &array[2]);
    print_test("El maximo es 5", heap_desencolar(heap) == &array[0]);
    print_test("El maximo es 3", heap_desencolar(heap) == &array[3]);
    print_test("El maximo es 2", heap_desencolar(heap) == &array[1]);
    print_test("El maximo es 1", heap_desencolar(heap) == &array[5]);
    print_test("El maximo es 0", heap_desencolar(heap) == &array[6]);
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

void pruebas_heapsort(){
    int array[]={9,3,4,6,1,2,5,7,8};
    int array_o[]={1,2,3,4,5,6,7,8,9};
    bool ok=true;
    heap_sort(array,9,comparar_void);
    for(int i=0; i<9;i++){
        ok&= array[i]==array_o[i];
    }
    print_test("El arreglo esta ordenado", ok);
}


void pruebas(){
    pruebas_encolar();
    pruebas_desencolar();
    pruebas_volumen_heap();
    pruebas_heapify();
    pruebas_heapsort();
}

int main() {
    pruebas();
    return 0;
}