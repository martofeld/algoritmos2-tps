cmake_minimum_required(VERSION 3.8)
project(tps)

set(CMAKE_C_STANDARD 99)

set(COMMONS testing.c)

set(SOURCE_FILES cola/cola.c cola/pruebas_alumno.c)
add_executable(cola ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES pila/pila.c pila/pruebas_alumno.c)
add_executable(pila ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES lista/lista.c lista/pruebas_alumno.c)
add_executable(lista ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES hash/hash.c hash/pruebas_catedra.c)
add_executable(hash ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES heap/heap.c heap/pruebas_alumnos.c)
add_executable(heap ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES abb/abb.c abb/pruebas_abb_alumno.c abb/pila.c)
add_executable(abb ${SOURCE_FILES} ${COMMONS})