//
// Created by Martin Feldsztejn on 10/9/17.
//

#include <stdlib.h>
#include "abb.h"
#include "pila.h"

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

bool abb_insertar_nodo(abb_t *abb, nodo_t *actual, nodo_t *nodo) {
    //TODO preguntar si compara como strcmp
    int comparacion = abb->comparar_clave(actual->clave, nodo->clave);
    if (comparacion == 0) {
        abb->destruir_dato(actual->valor);
        nodo_clave_destruir(actual->clave);
        actual->valor = nodo->valor;
        actual->clave = nodo->clave;
        free(nodo);
    } else if (comparacion < 0) {
        //La clave actual es mas chica, me voy a la derecha
        if (actual->der) {
            abb_insertar_nodo(abb, actual->der, nodo);
        } else {
            actual->der = nodo;
        }
    } else {
        //La clave actual es mas grande, me voy a la izq
        if (actual->izq) {
            abb_insertar_nodo(abb, actual->izq, nodo);
        } else {
            actual->izq = nodo;
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

void *abb_obtener_nodo(const abb_t *abb, nodo_t *nodo, const char *clave) {
    int comparacion = abb->comparar_clave(nodo->clave, clave);
    if (!nodo) {
        return NULL;
    }

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

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    nodo_t *nodo = abb_obtener_nodo(arbol, arbol->raiz, clave);
    return nodo != NULL;
}

// ----------- ITERADOR -----------
typedef struct abb_iter {
    pila_t *pila;
} abb_iter_t;

void apilar_izquierdos(pila_t *pila, nodo_t* inicio) {
    nodo_t* actual = inicio;
    while (actual) {
        pila_apilar(pila, actual);
        actual = actual->izq;
    }
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t *iter = malloc(sizeof(abb_iter_t));
    if (!iter) {
        return NULL;
    }

    pila_t *pila = pila_crear();
    if (!pila) {
        return NULL;
    }

    iter->pila = pila;
    apilar_izquierdos(iter->pila, arbol->raiz);
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) {
        return false;
    }
    nodo_t *actual = pila_desapilar(iter->pila);
    apilar_izquierdos(iter->pila, actual->der);
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) {
        return NULL;
    }
    nodo_t *actual = pila_ver_tope(iter->pila);
    return actual->clave;
}

void abb_iter_in_destruir(abb_iter_t *iter) {
    pila_destruir(iter->pila);
    free(iter);
}
// ----------- END ITERADOR -----------