
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "main.h"
#include "keyValue.h"
#include "sub.h"

#define BUFSIZE 1024 // Größe des Buffers
#define PORT 4711

int main() {
    char buffer[1024];

    int rfd; // Rendevouz-Descriptor
    int cfd; // Verbindungs-Descriptor

    initialize_array(); // Daten array mit "" füllen

    struct sockaddr_in client; // Socketadresse eines Clients
    socklen_t client_len; // Länge der Client-Daten
    char in[BUFSIZE]; // Daten vom Client an den Server
    int bytes_read; // Anzahl der Bytes, die der Client geschickt hat

    pid_t childpid; // Child Process-ID (gebraucht für mehrere Clients)

    // Socket erstellen
    rfd = socket(AF_INET, SOCK_STREAM, 0);
    if (rfd < 0 ){
        fprintf(stderr, "socket konnte nicht erstellt werden\n");
        exit(-1);
    }


    // Socket Optionen setzen für schnelles wiederholtes Binden der Adresse
    int option = 1;
    setsockopt(rfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));


    // Socket binden
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    int brt = bind(rfd, (struct sockaddr *) &server, sizeof(server));
    if (brt < 0 ){
        fprintf(stderr, "socket konnte nicht gebunden werden\n");
        exit(-1);
    }


    // Socket lauschen lassen
    int lrt = listen(rfd, 5);
    if (lrt < 0 ){
        fprintf(stderr, "socket konnte nicht listen gesetzt werden\n");
        exit(-1);
    }


    char out[out_size];

    int cnt = 0;
    while(1){
        // Verbindung eines Clients wird entgegengenommen
        cfd = accept(rfd, (struct sockaddr *) &client, &client_len);
        if (cfd < 0)
            exit(1);

        // Displaying information of connected client
        printf("Connection accepted from %s:%d\n",
               inet_ntoa(client.sin_addr),
               ntohs(client.sin_port));

        // Print number of clients connected till now
        printf("Clients connected: %d\n\n", ++cnt);

        // Creates a child process
        if (childpid = fork() == 0){ // FÜR MEHRERE CLIENTS VERANTWORTLICH !!!!!!!!!!
            // Closing the server socket id
            close(rfd);


            // Send a confirmation message to the client
            send(cfd, "hi client\n",
                 strlen("hi client\n"), 0);

            while(1){
                // Lesen von Daten, die der Client schickt
                bytes_read = read(cfd, in, BUFSIZE);

                // Zurückschicken der Daten, solange der Client welche schickt (und kein Fehler passiert)
                while (bytes_read > 0) {

                    // Splitten & Interpretierung von Input des Clients
                    proccess_client_input(in, &out);


                    write(cfd, out, strlen(out));
                    bytes_read = read(cfd, in, BUFSIZE);

                }
            }
        }
        close(cfd);
    }

    // Rendevouz Descriptor schließen
    close(rfd);
}
