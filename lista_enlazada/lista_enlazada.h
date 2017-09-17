#include <stdbool.h>
#include <stdlib.h>

typedef struct nodo nodo_t;
struct nodo {
    void *dato;
    nodo_t *proximo;
};

typedef struct lista_enlazada lista_enlazada_t;
struct lista_enlazada {
    size_t cantidad;
    nodo_t *primero;
    nodo_t *ultimo;
};

lista_enlazada_t *crear();

void destruir(lista_enlazada_t *lista);

void *ver_primero(lista_enlazada_t *lista);

void *ver_ultimo(lista_enlazada_t *lista);

bool insertar_primero(lista_enlazada_t *lista, void *dato);

bool insertar_ultimo(lista_enlazada_t *lista, void *dato);

void *borrar_primero(lista_enlazada_t *lista); //Devuelve el dato
bool esta_vacia(lista_enlazada_t *lista);
