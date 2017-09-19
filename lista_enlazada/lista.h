#include <stdbool.h>
#include <stdlib.h>

#ifndef LISTA_H
#define LISTA_H
typedef struct lista lista_t;

// PRIMITIVAS LISTA
lista_t *lista_crear(void);
bool lista_esta_vacia(const lista_t *lista);
bool lista_insertar_primero(lista_t *lista, void *dato);
bool lista_insertar_ultimo(lista_t *lista, void *dato);
void *lista_borrar_primero(lista_t *lista);
void *lista_ver_primero(const lista_t *lista);
void *lista_ver_ultimo(const lista_t* lista);
size_t lista_largo(const lista_t *lista);
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// PRIMITIVAS ITERADOR
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

#endif //LISTA_H
