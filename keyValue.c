//
// Created by sebastian on 09.05.2023.
//

#include "keyValue.h"
char buffer[out_size]; // Buffer for formatting output with sprintf()
char data[key_amount][value_lenght];
void initialize_array(){
    for(int i = 0; i<key_amount;i++)
    {
        strcpy(data[i], "");
    }
}

int get(int key, char *out[out_size]) {
    if (strcmp(data[key-1], "") != 0) {
        sprintf(buffer, "GET:key%d:",key);
        strcpy(*out, strcat(strcat(buffer, data[key-1]),"\n"));
        return 1;
    }
    else
    {
        strcpy(*out, "GET:key_empty\n");
        return 0;
    }
}
int put(int key,char value[value_lenght], char *out[out_size]){
    strcpy(data[key-1], value);
    sprintf(buffer, "PUT:key%d:",key);
    strcpy(*out, strcat(strcat(buffer, data[key-1]),"\n"));
    return 1;
}
int del(int key, char *out[out_size]){
    strcpy(data[key-1], "");
    sprintf(buffer, "DEL:key%d:",key);
    strcpy(*out, strcat(strcat(buffer, "key_cleared"),"\n"));
    return 1;

}
