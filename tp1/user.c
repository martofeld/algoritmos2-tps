//
// Created by Martin Feldsztejn on 9/30/17.
//
#include "user.h"
#include "stdlib.h"

struct user {
    int id;
    char* password;
    double balance;
};

user_t *create_user(int id, char *password, double balance) {
    user_t *user = malloc(sizeof(user_t));
    if (!user) {
        return NULL;
    }

    user->id=id;
    user->password = password;
    user->balance = balance;
    return user;
}

int user_get_id(user_t *user) {
    return user->id;
}

char* user_get_password(user_t *user) {
    return user->password;
}

double user_get_balance(user_t *user) {
    return user->balance;
}

void user_set_balance(user_t *user, double balance) {
    user->balance = balance;
}

void destroy_user(user_t *user) {
    free(user);
}