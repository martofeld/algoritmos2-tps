//
// Created by Martin Feldsztejn on 9/18/17.
//

#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pruebas_creacion() {
    lista_t *lista = lista_crear();

    print_test("La lista deberia estar vacia al crearse", lista_esta_vacia(lista));
    print_test("Ver primero deberia devolver NULL al crearse", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo deberia devolver NULL al crearse", lista_ver_ultimo(lista) == NULL);
    print_test("El largo de la lista deberia ser 0 al crearse", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
    print_test("La lista se destruyo correctamente", true);
}

void pruebas_agregar_primero() {
    lista_t *lista = lista_crear();

    int uno = 1;
    int dos = 2;

    print_test("Se inserta correctamente", lista_insertar_primero(lista, &uno));
    print_test("Ver primero deberia devolver 1", lista_ver_primero(lista) == &uno);

    print_test("Se inserta correctamente", lista_insertar_primero(lista, &dos));
    print_test("Ver primero deberia devolver 2", lista_ver_primero(lista) == &dos);

    print_test("Ver ultimo deberia devolver 1", lista_ver_ultimo(lista) == &uno);

    print_test("El tamaño deberia ser 2", lista_largo(lista) == 2);
    lista_destruir(lista, NULL);
}

void pruebas_agregar_ultimo() {
    lista_t *lista = lista_crear();

    int uno = 1;
    int dos = 2;

    print_test("Se inserta correctamente", lista_insertar_ultimo(lista, &uno));
    print_test("Ver ultimo deberia devolver 1", lista_ver_ultimo(lista) == &uno);

    print_test("Se inserta correctamente", lista_insertar_ultimo(lista, &dos));
    print_test("Ver ultimo deberia devolver 2", lista_ver_ultimo(lista) == &dos);

    print_test("Ver primero deberia devolver 1", lista_ver_primero(lista) == &uno);

    print_test("El tamaño deberia ser 2", lista_largo(lista) == 2);
    lista_destruir(lista, NULL);
}

void pruebas_borrar_primero() {
    lista_t *lista = lista_crear();

    int uno = 1;
    int dos = 2;

    print_test("Se inserta correctamente", lista_insertar_ultimo(lista, &uno));
    print_test("Se inserta correctamente", lista_insertar_ultimo(lista, &dos));
    print_test("El tamaño deberia ser 2", lista_largo(lista) == 2);
    print_test("Borrar primero deberia devolver 1", lista_borrar_primero(lista) == &uno);
    print_test("El tamaño deberia ser 1", lista_largo(lista) == 1);
    print_test("Borrar primero deberia devolver 2", lista_borrar_primero(lista) == &dos);
    print_test("La lista deberia estar vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

bool sumar(void *dato, void *extra) {
    int *int_dato = dato;
    *(int *) extra += *int_dato;
    return true;
}

void pruebas_iterar1() {
    int suma = 0;
    int array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    lista_t *lista = lista_crear();

    for (int i = 0; i < 9; i++) {
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iterar(lista, sumar, &suma);
    print_test("La suma de los elementos deberia ser 45", 45 == suma);

    lista_destruir(lista, NULL);
}

bool imprimir(void *dato, void *extra) {
    char *cadena = dato;
    if (strcmp("python", cadena) == 0) {
        return false;
    }
    strcat((char *) extra, cadena);
    strcat((char *) extra, " ");
    return true;
}

void pruebas_iterar2() {
    char *array[6] = {"Hola", "Mundo", "!", "Esto", "es", "C"};

    lista_t *lista = lista_crear();
    for (int i = 0; i < 6; i++) {
        lista_insertar_ultimo(lista, array[i]);
    }

    char cadena[24] = "";
    char expected[24] = "Hola Mundo ! Esto es C ";
    lista_iterar(lista, imprimir, &cadena);

    print_test("Se deberia haber concatenado correctamente", strcmp(cadena, expected) == 0);

    lista_destruir(lista, NULL);
}

void pruebas_iterar3() {
    char *array[7] = {"Hola", "Mundo", "python", "!", "Esto", "es", "Python"};

    lista_t *lista = lista_crear();
    for (int i = 0; i < 7; i++) {
        lista_insertar_ultimo(lista, array[i]);
    }

    char cadena[12] = "";
    char expected[12] = "Hola Mundo ";
    lista_iterar(lista, imprimir, &cadena);

    print_test("Se deberia haber concatenado correctamente", strcmp(cadena, expected) == 0);

    lista_destruir(lista, NULL);
}

void pruebas_de_volumen() {
    lista_t *lista = lista_crear();
    int array[10000];
    for (int i = 0; i < 10000; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    print_test("El tamaño deberia ser 10000", lista_largo(lista) == 10000);

    bool ok = true;
    for (int i = 0; i < 10000; ++i) {
        ok &= lista_borrar_primero(lista) == &array[i];
    }
    print_test("Todos los valores estaban bien", ok);

    lista_destruir(lista, NULL);
}

void destruir_dato_posta(int *dato) {
    *dato = -1;
}

void destruir_dato(void *dato) {
    destruir_dato_posta(dato);
}

void pruebas_destruyendo_dato() {
    lista_t *lista = lista_crear();
    int array[5];
    for (int i = 0; i < 5; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_destruir(lista, destruir_dato);

    bool datos_eliminados = true;
    for (int i = 0; i < 5; i++) {
        datos_eliminados &= array[i] == -1;
    }
    print_test("Los datos se borraron bien", datos_eliminados);
}

// --------- PRUEBAS ITERADOR ---------
void pruebas_creacion_iterador() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iter_t *iterador = lista_iter_crear(lista);
    print_test("El iterador arranca al principio de la lista", lista_iter_ver_actual(iterador) == &array[0]);
    print_test("El iterador no esta al final", !lista_iter_al_final(iterador));
    lista_iter_destruir(iterador);
    print_test("El iterador se destruyo", true);
    lista_destruir(lista, NULL);
}

void pruebas_avanzar() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iter_t *iterador = lista_iter_crear(lista);
    bool ok = true;
    int i = 0;
    while (!lista_iter_al_final(iterador)) {
        ok &= lista_iter_ver_actual(iterador) == &array[i];
        i++;
        lista_iter_avanzar(iterador);
    }

    print_test("El iterador avanza correctamente", ok && i == 9);
    print_test("El iterador esta al final", lista_iter_al_final(iterador));

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_borrar1() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iter_t *iterador = lista_iter_crear(lista);

    print_test("Borrar deberia borrar el primero correctamente", lista_iter_borrar(iterador) == &array[0]);
    print_test("El iterador esta en la segunda posicion", lista_iter_ver_actual(iterador) == &array[1]);
    print_test("La lista esta en la segunda posicion", lista_ver_primero(lista) == &array[1]);
    print_test("La lista tiene un elemento menos", lista_largo(lista) == 9);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_borrar2() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iter_t *iterador = lista_iter_crear(lista);
    while (!lista_iter_al_final(iterador)) {
        lista_iter_avanzar(iterador);
    }

    print_test("Borrar deberia borrar el ultimo correctamente", lista_iter_borrar(iterador) == &array[9]);
    print_test("El iterador esta al final", lista_iter_ver_actual(iterador) == NULL);
    print_test("La lista tiene bien el fin", lista_ver_ultimo(lista) == &array[8]);
    print_test("La lista tiene un elemento menos", lista_largo(lista) == 9);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_borrar3() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }

    lista_iter_t *iterador = lista_iter_crear(lista);
    int indice = 0;
    for (; indice < 6; indice++) {
        lista_iter_avanzar(iterador);
    }

    print_test("Borrar deberia borrar el ultimo correctamente", lista_iter_borrar(iterador) == &array[indice]);
    print_test("El iterador esta una poscion mas", lista_iter_ver_actual(iterador) == &array[indice + 1]);
    print_test("La lista tiene un elemento menos", lista_largo(lista) == 9);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_insertar1() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }
    int cuarenta = 40;

    lista_iter_t *iterador = lista_iter_crear(lista);

    print_test("Insertar deberia cambiar el primero correctamente", lista_iter_insertar(iterador, &cuarenta));
    print_test("El iterador esta en la segunda posicion", lista_iter_ver_actual(iterador) == &cuarenta);
    print_test("La lista tiene un nuevo primero", lista_ver_primero(lista) == &cuarenta);
    print_test("La lista tiene un elemento mas", lista_largo(lista) == 11);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_insertar2() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }
    int cuarenta = 40;

    lista_iter_t *iterador = lista_iter_crear(lista);
    while (!lista_iter_al_final(iterador)) {
        lista_iter_avanzar(iterador);
    }

    print_test("Insertar deberia cambiar el ultimo correctamente", lista_iter_insertar(iterador, &cuarenta));
    print_test("El iterador esta al final", lista_iter_ver_actual(iterador) == &cuarenta);
    print_test("La lista tiene bien el fin", lista_ver_ultimo(lista) == &cuarenta);
    print_test("La lista tiene un elemento mas", lista_largo(lista) == 11);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_insertar3() {
    lista_t *lista = lista_crear();
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
        lista_insertar_ultimo(lista, &array[i]);
    }
    int cuarenta = 40;

    lista_iter_t *iterador = lista_iter_crear(lista);
    int indice = 0;
    for (; indice < 6; indice++) {
        lista_iter_avanzar(iterador);
    }

    print_test("Insertar deberia cambiar alguno correctamente", lista_iter_insertar(iterador, &cuarenta));
    print_test("El iterador esta una poscion mas", lista_iter_ver_actual(iterador) == &cuarenta);
    print_test("La lista tiene un elemento mas", lista_largo(lista) == 11);

    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

void pruebas_lista_alumno(void) {
    printf("~~~~~~~ PRUEBAS LISTA ~~~~~~~\n");
    pruebas_creacion();
    pruebas_agregar_primero();
    pruebas_agregar_ultimo();
    pruebas_borrar_primero();
    pruebas_iterar1();
    pruebas_iterar2();
    pruebas_iterar3();
    pruebas_de_volumen();
    pruebas_destruyendo_dato();
    printf("~~~~~~~ PRUEBAS ITERADOR ~~~~~~~\n");
    pruebas_creacion_iterador();
    pruebas_avanzar();
    pruebas_borrar1();
    pruebas_borrar2();
    pruebas_borrar3();
    pruebas_insertar1();
    pruebas_insertar2();
    pruebas_insertar3();
}
