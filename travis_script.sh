#!/bin/bash
for dir in ./*/
do
    dir=${dir%*/}
    file=`echo "${dir##*/}" | tr '[a-z]' '[A-Z]'`
    echo "CORRIENDO PRUEBAS DE ${file}"
    cp testing.c $dir/testing.c
    cp testing.h $dir/testing.h
    gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o ${dir}/pruebas ${dir}/*.c
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=1 ${dir}/pruebas
    ${dir}/pruebas
    rm $dir/testing.c
    rm $dir/testing.h
done
