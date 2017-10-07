//
// Created by Martin Feldsztejn on 9/30/17.
//
#include "strutil.h"
#include "../testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_split(){
    char* string = "p1,p2,p3,p4,p5,p6,p7,p8";
    char** array = split(string, ',');

    int i = 0;
    size_t length = 0;
    while (array[i]){
        printf("The string in position %d matches", i);
        char* expected = malloc(3 * sizeof(char));
        snprintf(expected, 3, "p%d", i+1);
        print_test("", strcmp(expected, array[i]) == 0);
        length++;
        i++;
        free(expected);
    }

    free_strv(array);
}

void test_border_cases(){
    char** array = split("abc,,def", ',');
    print_test("Posicion 0 correcta", strcmp(array[0],"abc") == 0);
    print_test("Posicion 1 correcta", strcmp(array[1],"\0") == 0);
    print_test("Posicion 2 correcta", strcmp(array[2],"def") == 0);
    free_strv(array);

    array = split("abc,def,", ',');
    print_test("Posicion 0 correcta", strcmp(array[0],"abc") == 0);
    print_test("Posicion 1 correcta", strcmp(array[1],"def") == 0);
    print_test("Posicion 2 correcta", strcmp(array[2],"\0") == 0);
    free_strv(array);

    array = split(",abc,def", ',');
    print_test("Posicion 0 correcta", strcmp(array[0],"\0") == 0);
    print_test("Posicion 1 correcta", strcmp(array[1],"abc") == 0);
    print_test("Posicion 2 correcta", strcmp(array[2],"def") == 0);
    free_strv(array);

    array = split("", ',');
    print_test("Posicion 0 correcta", strcmp(array[0],"\0") == 0);
    free_strv(array);

    array = split(",", ',');
    print_test("Posicion 0 correcta", strcmp(array[0],"\0") == 0);
    print_test("Posicion 1 correcta", strcmp(array[1],"\0") == 0);

    free_strv(array);
}

void test_strutil(){
    test_split();
    test_border_cases();
}