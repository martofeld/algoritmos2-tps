//
// Created by Martin Feldsztejn on 11/2/17.
//

#include <stdlib.h>
#include "testing.h"
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
    int random_orden[] = {4, 2, 7, 5, 6, 8, 0};
    int ordered_indexes[] = {8, 7, 6, 5, 4, 2, 0};
    int largo = sizeof(random_orden) / sizeof(int);
    for (int i = 0; i < largo; i++) {
        heap_encolar(heap, &array[random_orden[i]]);
    }
    print_test("La cantidad es 7", heap_cantidad(heap) == 7);

    bool ok = true;
    for (int i = 0; i < largo; i++) {
        ok &= heap_desencolar(heap) == &array[ordered_indexes[i]];
    }

    print_test("El heap deberia estar vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

void pruebas_heapify() {
    int array[] = {5, 2, 7, 3, 8, 1, 0, 9};
    int ordered_indexes[] = {7, 4, 2, 0, 3, 1, 5, 6};
    size_t largo = sizeof(array) / sizeof(int);
    void *auxArray[largo];
    for (int i = 0; i < largo; i++) {
        auxArray[i] = &array[i];
    }
    heap_t *heap = heap_crear_arr(auxArray, largo, comparar_void);

    print_test("El maximo es 9", heap_ver_max(heap) == &array[7]);
    bool ok = true;
    for (int i = 0; i < largo; i++) {
        ok &= heap_desencolar(heap) == &array[ordered_indexes[i]];
    }
    print_test("Desencolo en orden de mayor a menor", ok);
}

void pruebas_volumen_heap(void) {
    heap_t *heap = heap_crear(comparar_void);
    int arreglo[VOLUMEN];
    bool OK = true;

//Aumentamos en cantidad el volumen de la heap
    for (int i = 0; i < VOLUMEN; i++) {
        arreglo[i] = i;
        OK &= heap_encolar(heap, &arreglo[i]);
    }

    print_test("Hace crecer el heap", OK);

    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("El largo del heap es 500", heap_cantidad(heap) == VOLUMEN);

//Vaciamos la heap

    for (int i = 0; i < VOLUMEN; i++) {
        heap_desencolar(heap);
    }

    print_test("El heap esta vacio", heap_esta_vacio(heap));

//La heap vaciada se comporta como recien creada

    print_test("Largo del heap es 0", !heap_cantidad(heap));
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void pruebas_heapsort() {
    int array[] = {9, 3, 4, 6, 1, 2, 5, 7, 8};
    int array_o[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int largo = sizeof(array) / sizeof(int);
    void *array_aux[largo];
    for (int j = 0; j < largo; j++) {
        array_aux[j] = &array[j];
    }
    bool ok = true;
    heap_sort(array_aux, 9, comparar_void);
    for (int i = 0; i < 9; i++) {
        ok &= *(int *) array_aux[i] == array_o[i];
    }
    print_test("El arreglo esta ordenado", ok);
}

void pruebas_destruyendo(){
    size_t largo = 10;
    heap_t* heap = heap_crear(comparar_void);
    int** array = malloc(sizeof(int*) * largo);
    for (int i = 0; i < largo; i++) {
        array[i] = malloc(sizeof(int));
        heap_encolar(heap, &array[i]);
    }
    print_test("El heap tiene 10 elementos", heap_cantidad(heap) == 10);
    heap_destruir(heap, free);
    free(array);
}

void pruebas_heap_alumno() {
    pruebas_encolar();
    pruebas_desencolar();
    pruebas_volumen_heap();
    pruebas_heapify();
    pruebas_heapsort();
    pruebas_destruyendo();
}

int main() {
    pruebas_heap_alumno();
    return 0;
}
