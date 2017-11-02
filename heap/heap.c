#include "heap.h"

#define INICIAL 15
#define REDIMENSION 2

struct heap {
    cmp_func_t cmp;
    void **arreglo;
    size_t largo;
    size_t cantidad;
};

// ----------- UTILS ----------
size_t hijo_izquierdo(size_t padre) {
    return (padre * 2) + 1;
}

size_t hijo_derecho(size_t padre) {
    return (padre * 2) + 2;
}

size_t buscar_padre(size_t hijo) {
    return (hijo - 1) / 2;
}

void swap(void **x, void **y) {
    void *aux = *x;
    *x = *y;
    *y = aux;
}

// Si devuelve -1 el primero es mayor
// Si devuelve 0 son iguales
// Si devuelve 1 el segundo es mayor
int comparar(cmp_func_t cmp, void *valor1, void *valor2) {
    return cmp(valor1, valor2);
}

void upheap(heap_t* heap, size_t posicion) {
    void** arreglo = heap->arreglo;
    size_t padre = buscar_padre(posicion);
    if (posicion == 0 || comparar(heap->cmp, arreglo[padre], arreglo[posicion]) <= 0) {
        return;
    }
    swap(&arreglo[posicion], &arreglo[padre]);
    upheap(heap, padre);
}

void downheap(heap_t *heap, size_t posicion, size_t largo) {
    void **arreglo = heap->arreglo;
    size_t hijo_izq = hijo_izquierdo(posicion);
    if (hijo_izq > largo) {
        //soy una hoja
        return;
    }
    size_t hijo_der = hijo_derecho(posicion);
    if (comparar(heap->cmp, arreglo[posicion], arreglo[hijo_izq]) < 0 &&
        comparar(heap->cmp, arreglo[posicion], arreglo[hijo_der]) < 0) {
        // El padre es mas grande que los dos hijos, todo cool
        return;
    }
    // Uno de los dos tiene que ser mas chico
    size_t pos_mayor = hijo_izq; // Asumo que es el izq
    if (comparar(heap->cmp, arreglo[posicion], arreglo[hijo_der]) > 0) { // El hijo derecho es mas grande
        pos_mayor = hijo_der;
    }
    swap(&arreglo[posicion], &arreglo[pos_mayor]);

    downheap(heap, pos_mayor, largo);
}
// ------------ END UTILS ---------

heap_t *_crear_heap(cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap));
    if (!heap) {
        return NULL;
    }
    heap->largo = INICIAL;
    heap->cantidad = 0;
    heap->cmp = cmp;
    return heap;
}

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t *heap = _crear_heap(cmp);
    if (!heap) return NULL;
    void *arreglo = malloc(sizeof(void *) * INICIAL);
    if (!arreglo) {
        free(heap);
        return NULL;
    }
    heap->arreglo = arreglo;
    return heap;
}

void heapify(heap_t *heap, size_t n, size_t i) {
    size_t k = buscar_padre(n) + 1;
    do {
        downheap(heap, k - 1, n);
        k--;
    } while (k > 0); // Para fixear que el size_t no puede ser negativo
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = _crear_heap(cmp);
    if (!heap) return NULL;
    heap->arreglo = arreglo;
    heapify(heap, n, n);
    return heap;
}


bool redimensionar(heap_t *heap, size_t largo_nuevo) {
    void **arreglo = heap->arreglo;
    void *arreglo_nuevo = realloc(arreglo, sizeof(void *) * largo_nuevo);
    if (!arreglo_nuevo) {
        return false;
    }
    heap->arreglo = arreglo_nuevo;
    heap->largo = largo_nuevo;
    return true;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
    if(destruir_elemento) {
        for (int i = 0; i < heap->cantidad; i++) {
            destruir_elemento(heap->arreglo[i]);
        }
    }
    free(heap->arreglo);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;

}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cantidad == 0;
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cantidad + 1 == heap->largo) {
        size_t largo_nuevo = heap->largo * REDIMENSION;
        if (!redimensionar(heap, largo_nuevo)) {
            return false;
        }
    }
    heap->arreglo[heap->cantidad] = elem;
    upheap(heap, heap->cantidad);
    heap->cantidad++;
    return true;
}

void *heap_ver_max(const heap_t *heap) {
    return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap) {
    void *desencolado = heap->arreglo[0];
    heap->arreglo[0] = heap->arreglo[heap->cantidad - 1];
//    free(heap->arreglo[heap->cantidad - 1]);
    downheap(heap, 0, heap->cantidad);
    heap->cantidad--;
    return desencolado;

}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {


}
