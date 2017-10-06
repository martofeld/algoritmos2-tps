//
// Created by Martin Feldsztejn on 10/5/17.
//

#include "hash.h"
#include "lista.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10

typedef struct hash_item {
    char *clave;
    void *valor;
} hash_item_t;

struct hash {
    lista_t **tabla;
    size_t n; // Cantidad
    size_t m; // Capacidad
    hash_destruir_dato_t destruir_dato;
};

size_t fnv1a_hash(const char *cp) {
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return hash;
}

size_t *hash_value(hash_t *hash, const char *clave) {
    return fnv1a_hash(clave) % hash->m;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash) {
        return NULL;
    }

    hash->tabla = malloc(sizeof(hash_item_t) * CAPACIDAD_INICIAL);
    for (int i = 0; i < CAPACIDAD_INICIAL; i++) {
        hash->tabla[i] = lista_crear();
    }
    hash->n = 0;
    hash->m = CAPACIDAD_INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    size_t hash_key = hash_value(hash, clave);
    lista_t *lista = hash->tabla[hash_key];
    if (lista) {
        lista_iter_t *iter = buscar(lista, clave);
        if (lista_iter_al_final(iter)) {
            return NULL;
        }
        void *valor = lista_iter_ver_actual(iter)->valor;
        lista_iter_destruir(iter);
        return valor;
    }
    return NULL;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    size_t hash_key = hash_value(hash, clave);
    lista_t *lista = hash->tabla[hash_key];
    if (lista) {
        lista_iter_t* iter = buscar(lista, clave);
        if (lista_iter_al_final(iter)) {
            return NULL;
        }
        void *valor = ((hash_item_t *) lista_iter_borrar(iter))->valor;
        lista_iter_destruir(iter);
        return valor;
    }
    return NULL;
}

lista_iter_t *buscar(lista_t *lista, const char *clave) {
    lista_iter_t *iter = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter) && strcmp(lista_iter_ver_actual(iter)->clave, clave) != 0) {
        lista_iter_avanzar(iter);
    }
    return iter;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->n;
}