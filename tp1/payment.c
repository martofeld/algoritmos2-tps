//
// Created by Martin Feldsztejn on 9/30/17.
//
#include <stdio.h>
#include <string.h>
#include "payment.h"
#include "stdlib.h"
#include "strcopy.h"
#include "tdas/pila.h"
#include "strutil.h"

#define VALIDATE_USER "validar_usuario"
#define VALIDATE_PAYMENT "validar_pago"
#define PAY "pagar"

struct payment {
    int id;
    char *code;
    double amount;
};

payment_t *create_payment_and_enqueue(int id, double amount, char *code, cola_t *payment_queue) {
    payment_t *payment = malloc(sizeof(payment_t));
    if (!payment) {
        return NULL;
    }

    payment->amount = amount;
    payment->code = strcopy(code);
    payment->id = id;
    cola_encolar(payment_queue, payment);
    return payment;
}

int payment_get_id(payment_t *payment) {
    return payment->id;
}

char *payment_get_code(payment_t *payment) {
    return payment->code;
}

double payment_get_amount(payment_t *payment) {
    return payment->amount;
}

void destroy_payment(payment_t *payment) {
    free(payment->code);
    free(payment);
}

/**
 * Validates a payment. Checks if the user has enough balance to make the transaction
 * @param users
 * @param amount
 * @param id
 * @return
 */
bool validate_payment(user_t **users, double amount, int id) {
    user_t *user = users[id];
    return user && user_get_balance(user) >= amount && user_get_id(user) == id;
}

/**
 * Transfers amount from user 1 to user 2
 * @param users
 * @param user1_id
 * @param user2_id
 * @param amount
 * @return
 */
bool pay(user_t **users, int user1_id, int user2_id, double amount) {
    user_t *user2 = users[user2_id];
    user_t *user1 = users[user1_id];
    if (!user2 || !user1) {
        return false;
    }
    user_add_balance(user2, amount);
    user_take_balance(user1, amount);
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
        char **splited_code = split(code, PAYMENT_CODE_SEPARATOR);
        int i = 0;
        bool payment_success = true;
        while (splited_code[i] && payment_success) {
            if (strcmp(splited_code[i], VALIDATE_USER) == 0) {
                char *coordinates = pila_desapilar(stack);
                int id = atoi(pila_desapilar(stack));
                if (!validate_user(users, coordinates, id)) {
                    fprintf(stderr, "Error en pago %d\n", payment_get_id(payment));
                    payment_success = false;
                }
            } else if (strcmp(splited_code[i], VALIDATE_PAYMENT) == 0) {
                double amount = atof(pila_desapilar(stack));
                int id = atoi(pila_desapilar(stack));
                if (!validate_payment(users, amount, id)) {
                    fprintf(stderr, "Error en pago %d\n", payment_get_id(payment));
                    payment_success = false;
                }
            } else if (strcmp(splited_code[i], PAY) == 0) {
                int id1 = atoi(pila_desapilar(stack));
                int id2 = atoi(pila_desapilar(stack));
                double amount = atof(pila_desapilar(stack));
                if (!pay(users, id1, id2, amount)) {
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