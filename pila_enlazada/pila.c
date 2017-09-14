#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define PILA_TAMANO_INICIAL 20
#define MULTIPLICADOR_TAMANO 2
#define PILA_VACIA 0

/* Definición del struct pila proporcionado por la cátedra.
 */

typedef struct nodo nodo_t;
struct nodo {
    void *dato;
    node_t *proximo;
}

struct pila {
    nodo_t *tope;
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear() {
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL) {
        return NULL;
    }
    pila->tope = NULL;

    return pila;
}

void pila_destruir(pila_t *pila) {
    nodo_t *actual = pila->tope;
    while (actual) {
        free(actual);
    }
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return pila->tope != NULL;
}

bool pila_apilar(pila_t *pila, void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return false;
    }

    nodo->dato = valor;
    nodo->proximo = pila->tope;
    pila->tope = nodo;
    return true;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }

    return pila->tope->dato;
}

void *pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }

    nodo_t *nodo = pila->tope;
    pila->tope = nodo->proximo;
    void *resultado = nodo->dato;
    free(nodo)
    return resultado;
}
