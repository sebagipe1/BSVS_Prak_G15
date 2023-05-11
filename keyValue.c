//
// Created by sebastian on 09.05.2023.
//

#include "keyValue.h"
#include <stdio.h>
#include <string.h>
char buffer[out_size]; // Buffer for formatting output with sprintf()
char data[key_amount][value_lenght];
void initialize_array(){
    for(int i = 0; i<key_amount;i++)
    {
        strcpy(data[i], "");
    }
   strcpy(data[0], "Tom");

}

int get(int key, char *out[out_size]) {
    if (strcmp(data[key-1], "") != 0) {
        sprintf(buffer, "GET:key%d:",key);
        strcpy(*out, strcat(strcat(buffer, data[key-1]),"\n"));
        return 1;
    }
    else
    {
        strcpy(*out, "GET:key_nonexistent\n");
        return 0;
    }

}
