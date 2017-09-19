#!/bin/bash
for dir in ./*/
do
    dir=${dir%*/}
    file=`echo "${dir##*/}" | tr '[a-z]' '[A-Z]'`
    echo "CORRIENDO PRUEBAS DE ${file}"
    gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ${dir}/pruebas ${dir}/*.c testing.c
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ${dir}/pruebas
    ${dir}/pruebas
done
