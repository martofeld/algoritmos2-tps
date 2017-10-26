set(COMMON_SOURCE_CODE testing.c)

set(COLA_SOURCE_CODE cola/cola.c cola/pruebas_alumno.c cola/main.c ${COMMON_SOURCE_CODE})
add_executable(cola ${COLA_SOURCE_CODE})

set(HASH_SOURCE_CODE hash/hash.c hash/lista.c hash/pruebas_catedra.c hash/main.c ${COMMON_SOURCE_CODE})
add_executable(hash ${HASH_SOURCE_CODE})