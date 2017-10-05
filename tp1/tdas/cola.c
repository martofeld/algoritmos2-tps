#include <stdlib.h>
#include "cola.h"
#include "nodo.h"

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
    return !cola->primero && !cola->ultimo;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo = nodo_crear(valor, NULL);

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
    if (!cola->primero) {
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
    while (!cola_esta_vacia(cola)) {
        void* dato = cola_desencolar(cola);
        if (destruir_dato != NULL) {
            destruir_dato(dato);
        }
    }
    free(cola);
}
