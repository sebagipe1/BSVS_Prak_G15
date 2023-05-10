//
// Created by sebastian on 09.05.2023.
//

#ifndef BSVS_PRAK_G15_KEYVALUE_H
#define BSVS_PRAK_G15_KEYVALUE_H
#define value_lenght 10 // max lenght for values
#define key_amount 10 //Amount keys (indexes) in the Data array
int get(int key, char *out);
int put(char* key, char* res);
int del(char* key);
#endif //BSVS_PRAK_G15_KEYVALUE_H
