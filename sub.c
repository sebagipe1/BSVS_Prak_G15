//
// Created by sebastian on 09.05.2023.
//

#include "sub.h"
#include "keyValue.h"



#define delim " "

int proccess_client_input(char in[], char *out[out_size]) {
    // Splitten & Interpretierung von Input des Clients
    int key;
    char *ptr; // Char pointer. (For splitting the Client input)
    ptr = strtok(in, delim);
    ptr = strtok(NULL, delim);
    if (ptr != NULL && strcmp(ptr, "0") != 0) {
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

void client_connection(){
    int PID = fork();
    // Verbindung eines Clients wird entgegengenommen
    cfd = accept(rfd, (struct sockaddr *) &client, &client_len);

    // Lesen von Daten, die der Client schickt
    bytes_read = read(cfd, in, BUFSIZE);
    if(strcmp(in, "quit") == 0)
    {
        close(cfd);
    }
    else {
        // Zurückschicken der Daten, solange der Client welche schickt (und kein Fehler passiert)
        while (bytes_read > 0) {

            // Splitten & Interpretierung von Input des Clients
            proccess_client_input(in, &out);


            write(cfd, out, strlen(out));
            bytes_read = read(cfd, in, BUFSIZE);

        }
    }
}
