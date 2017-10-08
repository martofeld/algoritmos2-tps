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
    free(item->clave);
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
    size_t largo= strlen(clave);
    char* clave_aux= malloc(sizeof(char)*(largo+1));
    strcpy(clave_aux,clave);
    item->clave = clave_aux;
    item->valor = dato;
    return item;
}


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

typedef struct hash_iter{
    hash_t* hash;
    size_t iterados;
    size_t indice;
    iter_lista_t* iter_lista;

}hash_iter_t;

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* iter= malloc(sizeof(hash_iter_t));
    if (!iter){
        return NULL;
    }
    iter->hash= hash;
    iter->iterados=0;
    iter->indice=0;
    lista_t* lista= buscar_proximo(hash, iter->indice);
    lista_iter_t* iter_lista= lista_iter_crear(lista);
    if (!iter_lista){
        return NULL;
    }
    iter->iter_lista=iter_lista;
    return iter;    
}


bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->iterados==iter->hash->n;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if(hash_iter_al_final(iter)){
        return false;
    }
    if(lista_iter_al_final(iter->iter_lista)){
        lista_iter_destruir(iter->iter_lista);
        iter->indice++;
        lista_t* lista= buscar_proximo(iter, iter->indice);
        iter_lista_t* iter_lista= lista_iter_crear(lista);
        if(!iter){
            return false;
        }
        iter->iter_lista=iter_lista;
    }
    iter->iterados++;
    return lista_iter_avanzar(iter->iter_lista);
} 

lista_t* buscar_proximo(hash_iter_t* iter, int indice){
    while(lista_esta_vacia(iter->hash->tabla[indice])){
        indice++;
    }
    iter->indice=indice;
    return iter->hash->tabla[indice];
>>>>>>> e45f422bc7e49b93c5a3f043391d2e6d3127e40e
}