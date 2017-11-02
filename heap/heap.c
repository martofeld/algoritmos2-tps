#include "heap.h"
#define INICIAL 15
#define REDIMENSION 2

struct heap{
	void** arreglo;
	size_t largo;
	size_t cantidad;
};

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap= malloc(sizeof(heap));
	if(!heap){
		return NULL;
	}
	void* arreglo= malloc(sizeof(void)*INICIAL);
	if(!arreglo){
		free(heap):
		return NULL;
	}
	heap->arreglo=arreglo;
	heap->largo=INICIAL;
	heap->cantidad=0:
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	for(int i=0;i<heap->cantidad;i++){
		destruir_elemento(heap->arreglo[i]);
	}
	free(heap->arreglo);
	free(arreglo);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;

}
bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad==0;

}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap->cantidad+1> heap->largo){
		size_t cap_nueva= heap->capacidad * REDIMENSION;
		if(!redimensionar(heap,cap_nueva)){
			return false;
		}
	}
	heap->arreglo[heap->cantidad]=elem;
	heap->cantidad++:
	upheap(heap->arreglo,heap->largo);
	return true;
}

void *heap_ver_max(const heap_t *heap){
	return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap){
	void* desencolado=heap->areglo[0];
	heap->arreglo[0]= heap->arreglo[heap->cantidad-1];
	free(heap->arreglo[heap->cantidad-1]);
	downheap(heap->arreglo);
	heap->cantidad--;
	return desencolado;

}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){


}

void upheap(void** arreglo, size_t posicion){
	int padre= padre(posicion);
	if (posicion==0 || arreglo[padre] > arreglo[posicion]){
		return;
	}
	swap(&arreglo[posicion], &arreglo[padre]);
	upheap(heap, padre);
}

void downheap(void** arreglo, size_t posicion, size_t largo){
	int hijo_izq = hijo_izq(posicion);
	if(hijo_izq > largo){
		//soy una hoja
		return;
	}
	int hijo_der = hijo_der(posicion);
	if(arreglo[posicion] > arreglo[hijo_izq] && arreglo[posicion] > arreglo[hijo_der]){
		return;
	}

	if(arreglo[posicion] < arreglo[hijo_izq] || arreglo[posicion] < arreglo[hijo_der]){//utilizar funcio de comparacion
		int pos_mayor= hijo_izq;
		if(arreglo[hijo_der]<arreglo[mayor]){
			mayor= hijo_der;
		}
		swap(&arreglo[posicion], &arreglo[pos_mayor]);
	}

	downheap(arreglo,pos_mayor,largo);

}

int hijo_izq(int padre){
	return padre * 2 + 1;
}

int hijo_der(int padre){
	return padre * 2 + 2;
}

int padre(int hijo){
	return hijo-1 /2;
}

bool redimensionar(heap_t *heap, size_t cap_nueva){
	void* arreglo_nuevo= realloc(heap->arreglo, sizeof(void)*cap_nueva);
	if(!arreglo_nuevo){
		return false;
	}
	heap->arreglo= arreglo_nuevo;
	heap->capacidad= cap_nueva;
	return true;
}

void swap (void* x, void* y) {
	void* aux= *x;
	*x= *y;
	*y= aux;
}


//GITHUB ME ODIA//


struct heap{
	void** arreglo;
	size_t largo;
	size_t cantidad;
};

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap= malloc(sizeof(heap));
	if(!heap){
		return NULL;
	}
	void* arreglo= malloc(sizeof(void*)*INICIAL);
	if(!arreglo){
		free(heap);
		return NULL;
	}
	heap->arreglo=arreglo;
	heap->largo=INICIAL;
	heap->cantidad=0;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
}

int hijo_izquierdo(int padre){
	return padre * 2 + 1;
}

int hijo_derecho(int padre){
	return padre * 2 + 2;
}

int buscar_padre(int hijo){
	return hijo-1 /2;
}

bool redimensionar(heap_t *heap, size_t largo_nuevo){
	void** arreglo= heap->arreglo;
	void* arreglo_nuevo= realloc(arreglo, sizeof(void*)*largo_nuevo);
	if(!arreglo_nuevo){
		return false;
	}
	heap->arreglo= arreglo_nuevo;
	heap->largo= largo_nuevo;
	return true;
}

void swap (void* x, void* y) {
	void* aux= x;
	x= y;
	y= aux;
}

void upheap(void** arreglo, size_t posicion){
	int padre= buscar_padre(posicion);
	if (posicion==0 || arreglo[padre] > arreglo[posicion]){
		return;
	}
	swap(&arreglo[posicion], &arreglo[padre]);
	upheap(arreglo, padre);
}

void downheap(void** arreglo, size_t posicion, size_t largo){
	int hijo_izq = hijo_izquierdo(posicion);
	if(hijo_izq > largo){
		//soy una hoja
		return;
	}
	int hijo_der = hijo_derecho(posicion);
	if(arreglo[posicion] > arreglo[hijo_izq] && arreglo[posicion] > arreglo[hijo_der]){
		return;
	}
	int pos_mayor;
	if(arreglo[posicion] < arreglo[hijo_izq] || arreglo[posicion] < arreglo[hijo_der]){//utilizar funcio de comparacion
		pos_mayor= hijo_izq;
		if(arreglo[hijo_der]<arreglo[pos_mayor]){
			pos_mayor= hijo_der;
		}
		swap(&arreglo[posicion], &arreglo[pos_mayor]);
	}

	downheap(arreglo,pos_mayor,largo);

}



void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	for(int i=0;i<heap->cantidad;i++){
		destruir_elemento(heap->arreglo[i]);
	}
	free(heap->arreglo);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;

}
bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad==0;

}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap->cantidad+1> heap->largo){
		size_t largo_nuevo= heap->largo * REDIMENSION;
		if(!redimensionar(heap,largo_nuevo)){
			return false;
		}
	}
	heap->arreglo[heap->cantidad]=elem;
	heap->cantidad++;
	upheap(heap->arreglo[heap->cantidad -1],heap->largo);
	return true;
}

void *heap_ver_max(const heap_t *heap){
	return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap){
	void* desencolado=heap->arreglo[0];
	heap->arreglo[0]= heap->arreglo[heap->cantidad-1];
	free(heap->arreglo[heap->cantidad-1]);
	downheap(heap->arreglo);
	heap->cantidad--;
	return desencolado;

}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){


}
