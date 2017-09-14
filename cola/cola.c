#include <stdlib.h>
#include "cola.h"

#define COLA_VACIA 0

struct nodo;
typedef struct nodo nodo_t;

struct nodo {
    void *dato;
    nodo_t *proximo;
};

nodo_t *nodo_crear(void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));

    if (!nodo) {
        return false;
    }

    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

void nodo_destruir(nodo_t *nodo) {
    free(nodo);
}

struct cola {
    nodo_t *primero;
    nodo_t *ultimo;
};

cola_t *cola_crear() {
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola) {
        return NULL;
    }

    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
    return !cola->primero || !cola->ultimo;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo = nodo_crear(valor);

    if (!nodo) {
        return false;
    }

    if (cola_esta_vacia(cola)) {
        cola->primero = nodo;
        cola->ultimo = nodo;
    } else {
        cola->ultimo->proximo = nodo;
        cola->ultimo = nodo;
    }
    return true;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }

    nodo_t *nodo = cola->primero;
    void *resultado = nodo->dato;
    cola->primero = nodo->proximo;
    nodo_destruir(nodo);
    if (cola_esta_vacia(cola)) {
        cola->ultimo = NULL; //Acabo de desencolar el ultimo, borro el ultimo
    }

    return resultado;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }

    return cola->primero->dato;
}

void cola_destruir(cola_t *cola, void destruir_dato(void *)) {
    if (destruir_dato != NULL) {
        nodo_t *actual = cola->primero;
        while (actual) {
            destruir_dato(actual->dato);
            nodo_t *proximo = actual->proximo;
            nodo_destruir(actual);
            actual = proximo;
        }
    }
    free(cola);
}
