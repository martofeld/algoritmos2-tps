//
// Created by Martin Feldsztejn on 9/30/17.
//
#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "payment.h"
#include "strutil.h"
#include "tdas/cola.h"
#include "tdas/pila.h"
#include "user.h"

#define NEW_PAYMENT "agregar_pago"
#define VIEW_PENDING "pagos_pendientes"
#define PROCESS "procesar"
#define SAVE "guardar_cuentas"
#define QUIT "finalizar"

#define VALIDATE_USER "validar_usuario"
#define VALIDATE_PAYMENT "validar_pago"
#define PAY "pagar"

/**
 * Creates a new payment and adds it to the queue
 * @param id
 * @param amount
 * @param code
 * @param payment_queue
 */
void new_payment(int id, double amount, char *code, cola_t *payment_queue) {
    payment_t *payment = create_payment(id, code, amount);
    cola_encolar(payment_queue, payment);
}

/**
 * Validates that a user id and coordinates match
 * @param users The list of users
 * @param coordinates  The user coordinates
 * @param id The user id
 * @return
 */
bool validate_user(user_t **users, void *coordinates, void *id) {
    char *coordinates_str = coordinates;
    int id_int = atoi((char*) id);
    user_t *user = users[id_int];
    return user && strcmp(user_get_password(user), coordinates_str) == 0 && user_get_id(user) == id_int;
}

/**
 * Validates a payment. Checks if the user has enough balance to make the transaction
 * @param users
 * @param amount
 * @param id
 * @return
 */
bool validate_payment(user_t **users, void *amount, void *id) {
    double amount_int = atof((char*) amount);
    int id_int = atoi((char*) id);
    user_t *user = users[id_int];
    return user && user_get_balance(user) >= amount_int && user_get_id(user) == id_int;
}

/**
 * Transfers amount from user 1 to user 2
 * @param users
 * @param user1_id
 * @param user2_id
 * @param amount
 * @return
 */
bool do_pay(user_t **users, void *user1_id, void *user2_id, void *amount) {
    int user1_id_int = atoi((char*) user1_id);
    int user2_id_int = atoi((char*) user2_id);
    double amount_int = atof((char*) amount);
    user_t *user2 = users[user2_id_int];
    user_t *user1 = users[user1_id_int];
    if (!user2 || !user1) {
        return false;
    }
    user_set_balance(user2, user_get_balance(user2) + amount_int);
    user_set_balance(user1, user_get_balance(user1) - amount_int);
    return true;
}

/**
 * Process n payments
 * @param n
 * @return
 */
void process_payments(int n, cola_t *payment_queue, user_t **users) {
    while (!cola_esta_vacia(payment_queue) && n > 0) {
        pila_t *stack = pila_crear();
        payment_t *payment = cola_desencolar(payment_queue);
        char *code = payment_get_code(payment);
        char **splited_code = split(code, ';');
        int i = 0;
        bool payment_success = true;
        while (splited_code[i] && payment_success) {
            if (strcmp(splited_code[i], VALIDATE_USER) == 0) {
                void* coordinates = pila_desapilar(stack);
                void* id = pila_desapilar(stack);
                if (!validate_user(users, coordinates, id)) {
                    fprintf(stderr, "Error en pago %d\n", payment_get_id(payment));
                    payment_success = false;
                }
            } else if (strcmp(splited_code[i], VALIDATE_PAYMENT) == 0) {
                void* amount = pila_desapilar(stack);
                void* id = pila_desapilar(stack);
                if (!validate_payment(users, amount, id)) {
                    fprintf(stderr, "Error en pago %d\n", payment_get_id(payment));
                    payment_success = false;
                }
            } else if (strcmp(splited_code[i], PAY) == 0) {
                void* id1 = pila_desapilar(stack);
                void* id2 = pila_desapilar(stack);
                void* amount = pila_desapilar(stack);
                if (!do_pay(users, id1, id2, amount)) {
                    fprintf(stderr, "Error en pago %d\n", payment_get_id(payment));
                    payment_success = false;
                }
            } else {
                pila_apilar(stack, splited_code[i]);
            }
            i++;
        }
        n--;
        free_strv(splited_code);
        destroy_payment(payment);
        pila_destruir(stack);
    }
}

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
    cola_t* aux_queue = cola_crear();
    int count = 0;
    double amount = 0;
    while (!cola_esta_vacia(payment_queue)){
        payment_t* payment = cola_desencolar(payment_queue);
        count++;
        amount += payment_get_amount(payment);
        cola_encolar(aux_queue, payment);
    }
    while (!cola_esta_vacia(aux_queue)){
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
        length++; //Cuento los parametros
    }
    
    int return_code = 0;
    if (strcmp(splited[0], NEW_PAYMENT) == 0) {
        if (length == 5) { // Because of NULL
            new_payment(atoi(splited[1]), atof(splited[2]), splited[3], payment_queue);
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
    if(return_code >= 0) {
        printf("OK\n");
    }
    return return_code;
}

user_t *create_user_from_file(char *line) {
    char **values = split(line, ',');
    user_t* user = create_user(atoi(values[0]), values[2], atof(values[1]));
    free_strv(values);
    return user;
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

user_t **read_users(const char *file_path) {
    FILE *users_file = fopen(file_path, "r");
    if (!users_file) {
        printf("Error while opening the file\n");
        return NULL;
    }
    size_t lines = count_lines(file_path);

    char *line = NULL;
    size_t length = 0;
    ssize_t read; //combo getline

    user_t **users = malloc(sizeof(user_t *) * (lines + 1));
    while ((read = getline(&line, &length, users_file)) > 0) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        user_t *user = create_user_from_file(line);
        if (user) {
            users[user_get_id(user)] = user;
        }
    }
    users[lines] = NULL; //Seteo el ultimo en NULL para poder iterar por los usuarios
    fclose(users_file);
    free(line);
    return users;
}

/**
 * Wrapper function to fulfill queue_destroy interface
 * @param value the value to destroy
 */
void destroy_payments(void *value) {
    destroy_payment(value);
}

int run(const char *file_path) {

    user_t **users = read_users(file_path);

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
