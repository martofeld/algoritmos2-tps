//
// Created by Martin Feldsztejn on 10/9/17.
//

#include <stdlib.h>
#include "abb.h"

typedef struct nodo nodo_t;
struct nodo {
    char *clave;
    void *valor;
    nodo_t *izq;
    nodo_t *der;
};

void nodo_clave_destruir(char *clave) {
    free(clave);
}

nodo_t *nodo_crear(const char *clave, void *valor) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return NULL;
    }
    //TODO copiar la clave
    nodo->clave = clave;
    nodo->valor = valor;
    nodo->der = NULL;
    nodo->izq = NULL;
}

void nodo_destruir(abb_destruir_dato_t destruir_dato, nodo_t *nodo) {
    if (destruir_dato) {
        destruir_dato(nodo->valor);
    }
    //TODO descomentar cuando copie la clave
    //nodo_clave_destruir(nodo->clave);
}

struct abb {
    abb_comparar_clave_t comparar_clave;
    abb_destruir_dato_t destruir_dato;
    nodo_t *raiz;
};

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t *abb = malloc(sizeof(abb_t));
    if (!abb) {
        return NULL;
    }
    abb->raiz = NULL;
    abb->comparar_clave = cmp;
    abb->destruir_dato = destruir_dato;
    return abb;
}

bool abb_insertar_nodo(abb_t *abb, nodo_t *actual, nodo_t *nuevo_nodo) {
    //TODO preguntar si compara como strcmp
    int comparacion = abb->comparar_clave(actual->clave, nuevo_nodo->clave);
    if (comparacion == 0) {
        abb->destruir_dato(actual->valor);
        actual->valor = nuevo_nodo->valor;
        free(nuevo_nodo);
    } else if (comparacion < 0) {
        //La clave actual es mas chica, me voy a la derecha
        if (actual->der) {
            abb_insertar_nodo(abb, actual->der, nuevo_nodo);
        } else {
            actual->der = nuevo_nodo;
        }
    } else {
        //La clave actual es mas grande, me voy a la izq
        if (actual->izq) {
            abb_insertar_nodo(abb, actual->izq, nuevo_nodo);
        } else {
            actual->izq = nuevo_nodo;
        }
    }
    return true;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    nodo_t *nodo = nodo_crear(clave, dato);
    if (!nodo) {
        return false;
    }
    if (!arbol->raiz) {
        arbol->raiz = nodo;
        return true;
    }

    return abb_insertar_nodo(arbol, arbol->raiz, nodo);
}

nodo_t *abb_obtener_nodo(const abb_t *abb, nodo_t *nodo, const char *clave) {
    if (!nodo) {
        return NULL;
    }
    int comparacion = abb->comparar_clave(nodo->clave, clave);

    if (comparacion == 0) {
        return nodo;
    } else if (comparacion < 0) {
        return abb_obtener_nodo(abb, nodo->der, clave);
    } else {
        return abb_obtener_nodo(abb, nodo->izq, clave);
    }
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    nodo_t *nodo = abb_obtener_nodo(arbol, arbol->raiz, clave);
    if (nodo) {
        return nodo->valor;
    }
    return NULL;
}