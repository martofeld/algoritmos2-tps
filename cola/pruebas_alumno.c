#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void pruebas_creacion() {
    cola_t *cola = cola_crear();

    print_test("La cola no deberia ser NULL al crearse", cola);
    print_test("La cola deberia estar vacia al crearse", cola_esta_vacia(cola));
    print_test("La cola recien creada deberia dar NULL al desencolar", cola_desencolar(cola) == NULL);
    print_test("La cola recien creada deberia dar NULL al ver primero", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
    print_test("La cola se destruyo", true);
}

void pruebas_encolar() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    cola_t *cola = cola_crear();
    bool encolo_bien = true;
    for (int i = 0; i < SIZE; i++) {
        encolo_bien &= cola_encolar(cola, &array[i]);
    }
    print_test("Encolo bien", encolo_bien);

    print_test("La cola no deberia estar vacia al encolar", !cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

void pruebas_desencolar() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    cola_t *cola = cola_crear();
    for (int i = 0; i < SIZE; i++) {
        cola_encolar(cola, &array[i]);
    }

    print_test("La cola no deberia estar vacia para desencolar", !cola_esta_vacia(cola));
    bool desencolo_bien = true;
    for (int i = 0; i < SIZE; i++) {
        desencolo_bien &= cola_desencolar(cola) == &array[i];
    }
    print_test("Desencolo bien", desencolo_bien);

    cola_destruir(cola, NULL);
}

void pruebas_ver_primero() {
    cola_t *cola = cola_crear();

    int uno = 1;
    cola_encolar(cola, &uno);
    int dos = 2;
    cola_encolar(cola, &dos);
    int tres = 3;
    cola_encolar(cola, &tres);

    bool ok = true;
    for (int i = 0; i < 5; i++) {
        ok &= cola_ver_primero(cola) == &uno;
    }
    print_test("ver primero deberia devolver 1", ok);

    cola_destruir(cola, NULL);
}

void destruir_dato(void *dato) {
    printf("Cambiando dato %d a -1 para simular destruccion\n", *((int *) dato));
    *((int *) dato) = -1; // Cambio el valor del dato a -1 para probar que se llamo
}

void pruebas_destruyendo_el_dato() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    cola_t *cola = cola_crear();
    for (int i = 0; i < SIZE; i++) {
        cola_encolar(cola, &array[i]);
    }

    cola_destruir(cola, destruir_dato);
    print_test("Destuyendo cola y datos", true);
    bool datos_invalidos = true;
    for (int i = 0; i < SIZE; i++) {
        datos_invalidos &= array[i] == -1;
    }
    print_test("Todos los datos deberian ser -1 luego de ser destruidos", datos_invalidos);
}

void pruebas_no_destruyendo_el_dato() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    cola_t *cola = cola_crear();
    for (int i = 0; i < SIZE; i++) {
        cola_encolar(cola, &array[i]);
    }

    cola_destruir(cola, NULL);
    bool datos_no_modificados = true;
    for (int i = 0; i < SIZE; i++) {
        datos_no_modificados &= array[i] == i;
    }
    print_test("Destuyendo cola, los datos no deberian ser modificados", datos_no_modificados);
}

void pruebas_con_null() {
    cola_t *cola = cola_crear();

    print_test("Encolar NULL es valido", cola_encolar(cola, NULL));
    print_test("La cola no esta vacia por mas que su valor sea NULL", !cola_esta_vacia(cola));
    print_test("Desencolar deberia devolver NULL", cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}

void pruebas_cola_alumno(void) {
    pruebas_creacion();
    pruebas_encolar();
    pruebas_desencolar();
    pruebas_ver_primero();
    pruebas_destruyendo_el_dato();
    pruebas_no_destruyendo_el_dato();
    pruebas_con_null();
}
