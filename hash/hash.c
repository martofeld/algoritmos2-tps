//
// Created by Martin Feldsztejn on 10/5/17.
//

#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>

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

size_t hash_value(const hash_t *hash, const char *clave) {
    return fnv1a_hash(clave) % hash->m;
}

lista_iter_t *buscar(lista_t *lista, const char *clave) {
    lista_iter_t *iter = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter) && strcmp(((hash_item_t *) lista_iter_ver_actual(iter))->clave, clave) != 0) {
        lista_iter_avanzar(iter);
    }
    return iter;
}

void hash_item_destruir(hash_item_t *item, hash_destruir_dato_t destruir_dato) {
    if (destruir_dato) {
        destruir_dato(item->valor);
    }
    //free(item->clave);
    free(item);
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

    lista_iter_t *iter = buscar(lista, clave);
    if (lista_iter_al_final(iter)) {
        return NULL;
    }
    void *valor = ((hash_item_t *) lista_iter_ver_actual(iter))->valor;
    lista_iter_destruir(iter);
    return valor;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    size_t hash_key = hash_value(hash, clave);
    lista_t *lista = hash->tabla[hash_key];

    lista_iter_t *iter = buscar(lista, clave);
    if (lista_iter_al_final(iter)) {
        return NULL;
    }
    hash_item_t* item = lista_iter_borrar(iter);
    void *valor = item->valor;
    hash_item_destruir(item, NULL);
    lista_iter_destruir(iter);
    hash->n--;
    return valor;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->n;
}

hash_item_t *crear_hash_item(const char *clave, void *dato) {
    hash_item_t *item = malloc(sizeof(hash_item_t));
    if (!item) {
        return NULL;
    }
    item->clave = clave; // Esto hay que copiarlo?
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

    size_t clave_h = hash_value(hash, clave);
    lista_t *lista = hash->tabla[clave_h];
    lista_iter_t *iter = buscar(lista, clave);
    if (lista_iter_ver_actual(iter)) {
        hash_item_t *item_viejo = lista_iter_borrar(iter);
        hash->n--;
        hash_item_destruir(item_viejo, hash->destruir_dato);
    }
    hash->n++;
    lista_iter_insertar(iter, item);
    lista_iter_destruir(iter);
    return true;

}//valor se libera

bool hash_pertenece(const hash_t *hash, const char *clave) {
    size_t clave_h = hash_value(hash, clave);
    lista_t *lista = hash->tabla[clave_h];
    lista_iter_t *iter = buscar(lista, clave);
    return !lista_iter_al_final(iter);
}

void hash_destruir(hash_t *hash) {
    for (int i = 0; i < hash->n; i++) {
        lista_t *lista = hash->tabla[i];
        lista_iter_t *iter = lista_iter_crear(lista);
        while (!lista_iter_al_final(iter)) {
            hash_item_destruir((hash_item_t *) lista_iter_borrar(iter), hash->destruir_dato);
        }
        lista_destruir(lista, NULL);
        lista_iter_destruir(iter);
    }
    free(hash->tabla);
    free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    return NULL;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    return NULL;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    return NULL;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    return NULL;
}

void hash_iter_destruir(hash_iter_t *iter) {

}