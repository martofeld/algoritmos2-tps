//
// Created by Martin Feldsztejn on 11/2/17.
//

#include "../testing.c"
#include "heap.h"

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

void pruebas() {
    pruebas_encolar();
    pruebas_desencolar();
    pruebas_heapify();
}

int main() {
    pruebas();
    return 0;
}