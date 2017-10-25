//
// Created by Martin Feldsztejn on 9/30/17.
//

#ifndef PROJECT_USER_H
#define PROJECT_USER_H
typedef struct user user_t;

user_t* create_user(int id, char* password, double balance);
int user_get_id(user_t* user);
char* user_get_password(user_t* user);
double user_get_balance(user_t* user);
void user_set_balance(user_t* user, double balance);
void destroy_user(user_t* user);
#endif //PROJECT_USER_H
