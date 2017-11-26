//
// Created by Martin Feldsztejn on 11/6/17.
//

#include <stdio.h>
#include "tp2.h"

int main(int argc, char const *argv[]) {
    if (argc != 1) {
        printf("Wrong arguments\n");
        return 1;
    }

    return start();
}
