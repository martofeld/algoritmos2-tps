//
// Created by Martin Feldsztejn on 9/30/17.
//

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

#include <stdbool.h>

typedef struct user user_t;

user_t *create_user(int id, char *password, double balance);

int user_get_id(user_t *user);

char *user_get_password(user_t *user);

double user_get_balance(user_t *user);

void destroy_user(user_t *user);

void user_add_balance(user_t *user, double amount);

void user_take_balance(user_t *user, double amount);

bool validate_user(user_t **users, char *coordinates, int id);

user_t** read_users_from_file(const char* file_path, size_t lines);

#endif //PROJECT_USER_H
