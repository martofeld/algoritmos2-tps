#include <stdlib.h>
#include "abb.h"
#include "string.h"
#include "../testing.c"

void prueba_insertar(){
	abb_t* abb = abb_crear(strcmp, NULL);
    int arr[] = {1,2,3,4,5};
    print_test("Se guardo un 0", abb_guardar(abb, "clave0", arr));
    print_test("Se guardo un 4", abb_guardar(abb, "clave4", arr + 4));
    print_test("Se guardo un 1", abb_guardar(abb, "clave1", arr + 1));
    print_test("Se guardo un 3", abb_guardar(abb, "clave3", arr + 3));
    print_test("Se guardo un 2", abb_guardar(abb, "clave2", arr + 2));
    print_test("Retorno un 4", abb_borrar(abb, "clave4") == arr+4);
    print_test("Retorno un 1", abb_borrar(abb, "clave1") == arr+1);
    print_test("Retorno un 3", abb_borrar(abb, "clave3") == arr+3);
    print_test("Retorno un 0", abb_borrar(abb, "clave0") == arr+0);
    print_test("Retorno un 2", abb_borrar(abb, "clave2") == arr+2);
    print_test("Retorno un NULL", !abb_borrar(abb, "clave4"));
    abb_destruir(abb);
}


void pruebas(){
	prueba_insertar();
}


int main(int argc, char const *argv[])
{
	pruebas();
	return 0;
}