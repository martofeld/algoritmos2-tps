//
// Created by Martin Feldsztejn on 9/30/17.
//
#include "payment.h"
#include "stdlib.h"

struct payment {
    int id;
    char *code;
    double amount;
};

payment_t *create_payment(int id, char *code, double amount) {
    payment_t *payment = malloc(sizeof(payment_t));
    if (!payment) {
        return NULL;
    }

    payment->amount = amount;
    payment->code = code;
    payment->id = id;
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
    free(payment);
}