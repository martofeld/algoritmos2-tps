//
// Created by Martin Feldsztejn on 10/4/17.
//
#include "nodo.h"
#include "stdlib.h"
#include "stdbool.h"

nodo_t *nodo_crear(void *valor, nodo_t* proximo) {
    nodo_t *nodo = malloc(sizeof(nodo_t));

    if (!nodo) {
        return false;
    }

    nodo->dato = valor;
    nodo->proximo = proximo;
    return nodo;
}

void nodo_destruir(nodo_t *nodo) {
    free(nodo);
}