#include "lista.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main() {
    /* Ejecuta todas las pruebas unitarias. */
    pruebas_lista_alumno();

    return failure_count() > 0;
}
