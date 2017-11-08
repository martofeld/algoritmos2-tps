//
// Created by Martin Feldsztejn on 9/30/17.
//
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "payment.h"
#include "strutil.h"

#define NEW_PAYMENT "agregar_pago"
#define VIEW_PENDING "pagos_pendientes"
#define PROCESS "procesar"
#define SAVE "guardar_cuentas"
#define QUIT "finalizar"

/**
 * Save the users to a file
 * @param file_name
 * @param users
 */
void save(char *file_name, user_t **users) {
    FILE *file = fopen(file_name, "w");
    size_t i = 0;
    while (users[i]) {
        user_t *user = users[i];
        fprintf(file, "%d,%.3f,%s\n", user_get_id(user), user_get_balance(user), user_get_password(user));
        i++;
    }
    fclose(file);
}

void view_pending(cola_t *payment_queue) {
    cola_t *aux_queue = cola_crear();
    int count = 0;
    double amount = 0;
    while (!cola_esta_vacia(payment_queue)) {
        payment_t *payment = cola_desencolar(payment_queue);
        count++;
        amount += payment_get_amount(payment);
        cola_encolar(aux_queue, payment);
    }
    while (!cola_esta_vacia(aux_queue)) {
        cola_encolar(payment_queue, cola_desencolar(aux_queue));
    }
    cola_destruir(aux_queue, NULL);
    printf("%d,%.3f\n", count, amount);
}

/**
 * Handles the possible inputs
 * @param line
 * @param payment_queue
 * @param users
 * @return
 */
int handle_input(char *line, cola_t *payment_queue, user_t **users) {
    char **splited = split(line, ' ');
    size_t length = 1;
    while (splited[length - 1]) {
        length++; //Count params
    }

    int return_code = 0;
    if (strcmp(splited[0], NEW_PAYMENT) == 0) {
        if (length == 5) { // Because of NULL
            create_payment_and_enqueue(atoi(splited[1]), atof(splited[2]), splited[3], payment_queue);
        } else {
            fprintf(stderr, "Error en comando %s\n", NEW_PAYMENT);
            return_code = -1;
        }
    } else if (strcmp(splited[0], PROCESS) == 0) {
        if (length == 3) {
            process_payments(atoi(splited[1]), payment_queue, users);
        } else {
            fprintf(stderr, "Error en comando %s\n", PROCESS);
            return_code = -1;
        }
    } else if (strcmp(splited[0], SAVE) == 0) {
        if (length == 3) {
            save(splited[1], users);
        } else {
            fprintf(stderr, "Error en comando %s\n", SAVE);
            return_code = -1;
        }
    } else if (strcmp(splited[0], VIEW_PENDING) == 0) {
        view_pending(payment_queue);
    } else if (strcmp(splited[0], QUIT) == 0) {
        return_code = 1; // Salgo para volver atras y liberar toda la memoria
    } else {
        fprintf(stderr, "Error en comando %s\n", splited[0]);
        return_code = -1;
    }
    free_strv(splited);
    if (return_code >= 0) {
        printf("OK\n");
    }
    return return_code;
}

size_t count_lines(const char *file_path) {
    size_t lines = 0;

    char *line = NULL;
    size_t length = 0;
    FILE *file = fopen(file_path, "r");
    while (getline(&line, &length, file) > 0) {
        lines++;
    }
    fclose(file);
    free(line);
    return lines;
}

/**
 * Wrapper function to fulfill queue_destroy interface
 * @param value the value to destroy
 */
void destroy_payments(void *value) {
    destroy_payment(value);
}

int start_wachencoin(const char *file_path) {

    user_t **users = read_users_from_file(file_path, count_lines(file_path));

    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline
    cola_t *payments_queue = cola_crear();
    while ((read = getline(&line, &length, stdin)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        if (handle_input(line, payments_queue, users) != 0) {
            break;
        }
    }
    free(line);
    cola_destruir(payments_queue, destroy_payments);
    for (int i = 0; users[i]; i++) {
        destroy_user(users[i]);
    }
    free(users);
    return 0;
}
