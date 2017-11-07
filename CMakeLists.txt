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

set(SOURCE_FILES tp1/payment.c tp1/user.c tp1/strutil.c tp1/tp1.c tp1/main.c tp1/tdas/pila.c tp1/tdas/cola.c)
add_executable(tp1 ${SOURCE_FILES} ${COMMONS})

set(SOURCE_FILES tp2/tp2.c tp2/strutil.c tp2/main.c tp2/tdas/hash.c tp2/tdas/lista.c)
add_executable(tp2 ${SOURCE_FILES} ${COMMONS})