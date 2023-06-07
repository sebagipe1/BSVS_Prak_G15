//
// Created by sebastian on 09.05.2023.
//

#ifndef BSVS_PRAK_G15_KEYVALUE_H
#define BSVS_PRAK_G15_KEYVALUE_H
#define value_lenght 10 // max lenght for values
#define key_amount 10 //Amount keys (indexes) in the Data array
#define out_size 7 + key_amount + value_lenght // Size of Output. Dependent on value length and key amount
#define delim ";"
#define BUFSIZE 1024
int get(int key, char *out[out_size]);
int put(int key,char value[value_lenght], char *out[out_size]);
int del(int key, char *out[out_size]);
char (*data)[key_amount][value_lenght];
char d_size[key_amount][value_lenght];
int cfd; // Verbindungs-Descriptor
char *ptr; // Char pointer. (For splitting the Client input)
void initialize_array();
#endif //BSVS_PRAK_G15_KEYVALUE_H