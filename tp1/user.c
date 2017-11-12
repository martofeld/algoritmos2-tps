//
// Created by Martin Feldsztejn on 9/30/17.
//
#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "strcopy.h"
#include "strutil.h"

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
    user->password = strcopy(password);
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

void user_add_balance(user_t* user, double amount){
    user->balance += amount;
}

void user_take_balance(user_t* user, double amount){
    user->balance -= amount;
}

void destroy_user(user_t *user) {
    free(user->password);
    free(user);
}

/**
 * Validates that a user id and coordinates match
 * @param users The list of users
 * @param coordinates  The user coordinates
 * @param id The user id
 * @return
 */
bool validate_user(user_t **users, char *coordinates, int id) {
    user_t *user = users[id];
    return user && strcmp(user_get_password(user), coordinates) == 0 && user_get_id(user) == id;
}

user_t *create_user_from_file(char *line) {
    char **values = split(line, ',');
    user_t *user = create_user(atoi(values[0]), values[2], atof(values[1]));
    free_strv(values);
    return user;
}

user_t** read_users_from_file(const char* file_path, size_t lines) {
    FILE *users_file = fopen(file_path, "r");
    if (!users_file) {
        printf("Error while opening the file\n");
        return NULL;
    }

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