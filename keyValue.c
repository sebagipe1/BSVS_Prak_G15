//
// Created by sebastian on 09.05.2023.
//

#include "keyValue.h"
#include <string.h>

char data[key_amount][value_lenght];

int get(int key, char *out) {
    if (data[key] != NULL) {
        out = "GET:KEY1:", data[key];
        return 1;
    }
    else
    {
        out = "GET:KEY1:key_nonexistent";
        return 0;
    }

}
