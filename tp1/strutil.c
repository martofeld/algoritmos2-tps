#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "strcopy.h"

int countSeparators(const char* str, char sep){
    int count = 0;
    int currentStringPosition = 0;
    while(str[currentStringPosition]) {
        if (str[currentStringPosition] == sep) count++;
        currentStringPosition++;
    }
    return count;
}

char** split(const char* str, char sep){
    int count = countSeparators(str, sep);

    char **array = (char **)malloc(sizeof(char *) * (count + 2));

    int currentStringPosition = 0;
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

char* strcopy(const char* src){
    char* dest = malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dest, src);
    return dest;
}

void free_strv(char *strv[]){
    for (int i = 0; strv[i]; i++) {
        free(strv[i]);
    }
	free(strv);
}
