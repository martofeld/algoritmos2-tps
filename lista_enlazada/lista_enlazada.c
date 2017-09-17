#include "lista_enlazada.h"

lista_enlazada_t *crear() {
    lista_enlazada_t *lista = malloc(sizeof(lista_enlazada_t));
    if (!lista) {
        return NULL;
    }
    lista->cantidad = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

void destruir(lista_enlazada_t *lista);

void *ver_primero(lista_enlazada_t *lista) {
    return lista->primero->dato;
}

void *ver_ultimo(lista_enlazada_t *lista) {
    return lista->ultimo->dato;
}

bool insertar_primero(lista_enlazada_t *lista, void *dato) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return false;
    }

    nodo->dato = dato;
    if (esta_vacia(lista)) {
        lista->ultimo = lista->primero = nodo;
    } else {
        nodo->proximo = lista->primero;
        lista->primero = nodo;
    }
    lista->cantidad++;
    return true;
}

bool insertar_ultimo(lista_enlazada_t *lista, void *dato) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return false;
    }

    nodo->dato = dato;
    nodo->proximo = NULL;
    if (esta_vacia(lista)) {
        lista->ultimo = lista->primero = nodo;
    } else {
        lista->ultimo->proximo = nodo;
        lista->ultimo = nodo;
    }
    lista->cantidad++;
    return true;
}

void *borrar_primero(lista_enlazada_t *lista) {
    nodo_t *primero = lista->primero;
    void *dato = primero->dato;
    lista->primero = primero->proximo;
    free(primero);
    lista->cantidad--;
    return dato;
}

bool esta_vacia(lista_enlazada_t *lista) {
    return lista->cantidad == 0 || !lista->primero || !lista->ultimo;
}
