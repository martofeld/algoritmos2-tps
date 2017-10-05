//
// Created by Martin Feldsztejn on 10/5/17.
//

#include "hash.h"
#include "lista.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10;

typedef struct hash_item {
    char *clave;
    void *valor;
};

struct hash {
    lista_t **tabla;
    size_t n; // Cantidad
    size_t m; // Capacidad
    hash_destruir_dato_t destruir_dato;
};

size_t fnv1a_hash(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return hash;
}

size_t* hash_value(hash_t* hash, const char* clave){
    return fnv1a_hash(clave) % hash->m;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash) {
        return NULL;
    }

    hash->n = 0;
    hash->m = CAPACIDAD_INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->n;
}