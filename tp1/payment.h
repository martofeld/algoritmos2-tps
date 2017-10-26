//
// Created by Martin Feldsztejn on 9/30/17.
//
#define PAYMENT_CODE_SEPARATOR ';'

#ifndef PROJECT_PAYMENT_H
#define PROJECT_PAYMENT_H

#include "tdas/cola.h"
#include "user.h"

typedef struct payment payment_t;

payment_t *create_payment_and_enqueue(int id, double amount, char *code, cola_t *payment_queue);

int payment_get_id(payment_t *payment);

char *payment_get_code(payment_t *payment);

double payment_get_amount(payment_t *payment);

void destroy_payment(payment_t *payment);

bool validate_payment(user_t **users, double amount, int id);

void process_payments(int n, cola_t *payment_queue, user_t **users);

#endif //PROJECT_PAYMENT_H
