//
// Created by Martin Feldsztejn on 9/30/17.
//

#ifndef PROJECT_PAYMENT_H
#define PROJECT_PAYMENT_H
typedef struct payment payment_t;

payment_t* create_payment(int id, char* code, double amount);
int payment_get_id(payment_t* payment);
char* payment_get_code(payment_t* payment);
double payment_get_amount(payment_t* payment);
void destroy_payment(payment_t* payment);

#endif //PROJECT_PAYMENT_H
