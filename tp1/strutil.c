#include <stdlib.h>
#include <string.h>
#include "stdio.h"

// strtok?
char** split(const char* str, char sep){
    int length = 0, count = 0;
    int currentStringPosition = 0;
    //Mientras haya cadena sigo
    while(str[currentStringPosition]) {
        if (str[currentStringPosition] == sep) count++; //Cuento la cantidad de espacios de array que voy a necesitar
        length++; // Cuento la cantidad de caracteres
   		currentStringPosition++;
    }
    currentStringPosition = 0;

    char **array = (char **)malloc(sizeof(char *) * (count + 2));
    int currentArrayPosition = 0;
    for(int i = 0; i < (count + 1); i++) {
        int j = 0;
        while(str[currentStringPosition + j] && str[currentStringPosition + j] != sep) j++;
 		j++;
        char* substring = (char *)malloc(sizeof(char) * j); //Reservo memoria para la cadena con su largo + 1 para el \0
        memcpy(substring, &str[currentStringPosition], (j-1));
        substring[j-1] = '\0';
        array[currentArrayPosition] = substring;
        currentStringPosition += j;
        currentArrayPosition++;
    }
    array[currentArrayPosition] = NULL;
    return array;  
}

void free_strv(char *strv[]){
	int i = 0;
	while(strv[i]){
		free(strv[i]);
		i++;
	}
	free(strv);
}