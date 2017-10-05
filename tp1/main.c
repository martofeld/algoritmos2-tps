#include "strutil.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char** array = split("Pepito,juancito,algo,otro,vos", ',');
	int i = 0;
	while(array[i]){
		printf("%s\n", array[i]);
		i++;
	}
    free_strv(array);

    test_strutil();

	return 0;
}

// Preguntas Je
// El amount podemos asumir que siempre es > 0?
// Que es el id del pago?
// que es el codigo del pago?
// que son las cadenas largas con ;