//
// Created by Martin Feldsztejn (101320) on 9/18/17.
//
#include "lista.h"

// --------- NODO ---------
typedef struct nodo nodo_t;
struct nodo {
    void *dato;
    nodo_t *proximo;
};

nodo_t *nodo_crear(void *dato) {
    return nodo_crear(dato, NULL);
}

nodo_t *nodo_crear(void *dato, nodo_t *proximo) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;

    nodo->dato = dato;
    nodo->proximo = proximo;
}

void nodo_destruir(nodo_t *nodo) {
    free(nodo);
}
// --------- END NODO ---------

// --------- LISTA ---------
struct lista_enlazada {
    size_t cantidad;
    nodo_t *primero;
    nodo_t *ultimo;
};

lista_t *lista_crear() {
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista) {
        return NULL;
    }
    lista->cantidad = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

size_t lista_largo(const lista_t *lista) {
    return lista->cantidad;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
    while (!lista_esta_vacia(lista)) {
        void *dato = lista_borrar_primero(lista);
        if (destruir_dato) {
            destruir_dato(dato);
        }
    }
    free(lista);
}

void *lista_ver_primero(lista_t *lista) {
    if (!lista->primero) return NULL;
    return lista->primero->dato;
}

void *lista_ver_ultimo(lista_t *lista) {
    if (!lista->ultimo) return NULL;
    return lista->ultimo->dato;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato, lista->primero);
    if (!nodo) {
        return false;
    }

    if (lista_esta_vacia(lista)) {
        lista->ultimo = nodo;
    }
    lista->primero = nodo;
    lista->cantidad++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) {
        return false;
    }

    if (lista_esta_vacia(lista)) {
        lista->primero = nodo;
    } else {
        lista->ultimo->proximo = nodo;
    }
    lista->ultimo = nodo;
    lista->cantidad++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    nodo_t *primero = lista->primero;
    void *dato = primero->dato;
    lista->primero = primero->proximo;
    nodo_destruir(primero);
    lista->cantidad--;

    if (lista->cantidad == 0) {
        lista->ultimo == NULL;
    }
    return dato;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->cantidad == 0 || !lista->primero || !lista->ultimo;
}
// --------- END LISTA ---------