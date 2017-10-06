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
    hash->n = 0;
    hash->m = CAPACIDAD_INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    size_t hash_key = hash_value(hash, clave);
    lista_t *list = hash->tabla[hash_key];
    if (list) {
        lista_iter_t *iter = lista_iter_crear(list);
        while (!lista_iter_al_final(iter) && strcmp(lista_iter_ver_actual(iter)->clave, clave) != 0) {
            lista_iter_avanzar(iter);
        }
        if (lista_iter_al_final(iter)) {
            return NULL;
        }
        return lista_iter_ver_actual(iter)->valor;
    }
    return NULL;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    size_t hash_key = hash_value(hash, clave);
    lista_t *list = hash->tabla[hash_key];
    if (list) {
        lista_iter_t *iter = lista_iter_crear(list);
        while (!lista_iter_al_final(iter) && strcmp(lista_iter_ver_actual(iter)->clave, clave) != 0) {
            lista_iter_avanzar(iter);
        }
        if (lista_iter_al_final(iter)) {
            return NULL;
        }
        return ((hash_item_t *) lista_iter_borrar(iter))->valor;
    }
    return NULL;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->n;
}

hash_item_t *crear_hash_item(const char *clave, void *dato) {
    hash_item_t *item = malloc(sizeof(hash_item_t));
    if (!item) {
        return NULL;
    }
    item->clave = clave;
    item->valor = dato;
    return item;
}

/**
 * Inserta un nodo a la lista..., si la clave se repite reemplaza
 * por el valor nuevo.
 * Pre: el hash fue creado.
 * Pos: Inserto un nodo con clave valor asociado.
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    hash_item_t *item = crear_hash_item(clave, dato);
    if (!item) {
        return false;
    }

    clave_h = hash_value(hash, clave);

    if (!hash->tabla[clave_h]) {
        lista_t *lista = lista_crear();
        if(!lista){
            free(item);
            return false;
        }
        lista_insertar_primero(lista, item);
        hash->tabla[clave_h] = lista;
    } else {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[clave_h]);
        while (!lista_iter_al_final(iter) && strcmp(lista_iter_ver_actual(iter)->clave, clave) != 0) {
            lista_iter_avanzar(iter);
        }
        if (lista_iter_al_final(iter)) {
            lista_iter_insertar(iter, item);
        } else {
            ((hash_item_t *) iter_ver_actual(iter))->valor = dato;
            free(item);
        }
        lista_iter_destruir(iter);
    }
    return true;

}//valor se libera

bool hash_pertenece(const hash_t *hash, const char *clave) {
    size_t clave_h = hash_value(hash, clave);
    if (!hash->tabla[clave_h]) {
        return false;
    }
    lista_t *lista = hash->tabla[clave_h];
    lista_iter *iter = lista_iter_crear(lista);

    while (!lista_iter_al_final(iter)) {
        if (strcmp((hash_item * (lista_iter_ver_actual(iter)))->clave, clave) == 0) {
            return true;
        }
        lista_iter_avanzar(iter);
    }
    return false;
}