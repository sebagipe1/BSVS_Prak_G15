//
// Created by sebastian on 09.05.2023.
//

#include "sub.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <sys/wait.h>

int proccess_client_input(char *ptr, char *out[out_size], char* in) {
    // Splitten & Interpretierung von Input des Clients
    int key;
    ptr = strtok(NULL, delim);
    if (ptr != NULL) {
        key = atoi(ptr);
        if (key > 0 && key <= key_amount) {
            if (strcmp(in, "GET") == 0) {
                get(key, &out);
                return 1;
            } else if (strcmp(in, "PUT") == 0) {
                ptr = strtok(NULL,delim);
                char v[value_lenght];
                strcpy(v,ptr);
                printf(v);
                if(ptr != NULL){
                    if(strlen(ptr) <= value_lenght){
                        put(key, v, &out);return 1;
                    }
                    else
                        strcpy(out, "Value too big to be stored");return 0;
                }
                else
                    strcpy(out, "PUT command missing value argument\n");
            } else if (strcmp(in, "DEL") == 0) {
                del(key, &out);
                return 1;
            }
            else
                strcpy(out, "Command Unknown\n");return 0;
        }
        else
            strcpy(out, "Key Out of Bounds\n");return 0;
    }
    strcpy(out, "Input not Valid\n");
    return 0;
}
