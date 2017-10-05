//
// Created by Martin Feldsztejn on 10/4/17.
//

#ifndef PROJECT_NODO_H
#define PROJECT_NODO_H
struct nodo;
typedef struct nodo nodo_t;
struct nodo {
    void *dato;
    nodo_t *proximo;
};

nodo_t *nodo_crear(void *valor, nodo_t* proximo);
void nodo_destruir(nodo_t *nodo);
#endif //PROJECT_NODO_H
