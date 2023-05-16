//
// Created by sebastian on 09.05.2023.
//

#ifndef BSVS_PRAK_G15_KEYVALUE_H
#define BSVS_PRAK_G15_KEYVALUE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define value_lenght 10 // max lenght for values
#define key_amount 10 //Amount keys (indexes) in the Data array
#define out_size 7 + key_amount + value_lenght // Size of Output. Dependent on value length and key amount
char out[out_size];
int rfd; // Rendevouz-Descriptor
int cfd; // Verbindungs-Descriptor
#define BUFSIZE 1024 // Größe des Buffers
int get(int key, char *out[out_size]);
int put(int key,char value[value_lenght], char *out[out_size]);
int del(int key, char *out[out_size]);
void initialize_array();
struct sockaddr_in client; // Socketadresse eines Clients
socklen_t client_len; // Länge der Client-Daten
char in[BUFSIZE]; // Daten vom Client an den Server
int bytes_read; // Anzahl der Bytes, die der Client geschickt hat
#endif //BSVS_PRAK_G15_KEYVALUE_H
