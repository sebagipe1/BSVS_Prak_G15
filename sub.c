//
// Created by sebastian on 09.05.2023.
//

#include "sub.h"
#include "keyValue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define delim " "

void proccess_client_input(char in[], char* out) {
    // Splitten & Interpretierung von Input des Clients
    int key;
    char*ptr; // Char pointer. (For splitting the Client input)
    ptr = strtok(in, delim);
    if(ptr == "GET"){
        ptr = strtok(NULL, delim);
        key = atoi(ptr);
        get(key, &out);
        out = "GET:KEY1:key_nonexistent";

    }
    else if (ptr == "PUT"){

    }
    else if(ptr == "DEL"){}
}
