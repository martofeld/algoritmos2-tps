#include "pila.h"
#include "../testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void prubas_creacion_pila() {
    pila_t *pila = pila_crear();

    print_test("La pila no deberia ser NULL", pila != NULL);
    print_test("La pila deberia estar vacia", pila_esta_vacia(pila));

    pila_destruir(pila);
    print_test("La pila fue destruida", true);
}

void pruebas_apilar_desapilar() {
    pila_t *pila = pila_crear();

    int uno = 1;
    pila_apilar(pila, &uno);
    int dos = 2;
    pila_apilar(pila, &dos);
    int tres = 3;
    pila_apilar(pila, &tres);

    print_test("La pila no deberia estar vacia luego de apilar", !pila_esta_vacia(pila));
    print_test("Desapilar deberia devolver 3", *((int *) pila_desapilar(pila)) == 3);
    print_test("Desapilar deberia devolver 2", *((int *) pila_desapilar(pila)) == 2);
    print_test("Desapilar deberia devolver 1", *((int *) pila_desapilar(pila)) == 1);
    print_test("La pila deberia estar vacia luego de desapilar", pila_esta_vacia(pila));

    pila_destruir(pila);
}

void pruebas_ver_tope() {
    pila_t *pila = pila_crear();

    int uno = 1;
    pila_apilar(pila, &uno);
    int dos = 2;
    pila_apilar(pila, &dos);
    int tres = 3;
    pila_apilar(pila, &tres);

    for (int i = 0; i < 5; i++) {
        printf("En la vez %d, ", i);
        print_test("ver tope deberia devolver 3", *((int *) pila_ver_tope(pila)) == 3);
    }

    pila_destruir(pila);
}

void pruebas_redimensionar() {
    pila_t *pila = pila_crear();

    int *arreglo = malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        arreglo[i] = i;
    }

    bool apilo_ok = true;
    for (int i = 0; i < 100; i++) {
        apilo_ok &= pila_apilar(pila, &arreglo[i]);
    }
    print_test("Apilo ok", apilo_ok);

    bool desapilo_ok = true;
    for (int i = 99; i >= 0; i--) {
        desapilo_ok &= pila_desapilar(pila) == &arreglo[i];
    }
    print_test("Desapilo ok", desapilo_ok);

    free(arreglo);
    pila_destruir(pila);
}

void pruebas_pila_vacia() {
    pila_t *pila = pila_crear();

    print_test("Ver tope deberia dar NULL con la pila vacia", pila_ver_tope(pila) == NULL);
    print_test("Desapila deberia dar NULL con la pila vacia", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

void pruebas_con_null() {
    pila_t *pila = pila_crear();

    print_test("Apilar NULL es un valor valido", pila_apilar(pila, NULL));
    print_test("La pila no esta vacia por mas que su valor sea NULL", !pila_esta_vacia(pila));
    print_test("Desapilar deberia devolver NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

void pruebas_pila_alumno() {
    prubas_creacion_pila();
    pruebas_apilar_desapilar();
    pruebas_ver_tope();
    pruebas_redimensionar();
    pruebas_pila_vacia();
}
