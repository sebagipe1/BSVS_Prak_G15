#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include "main.h"
#include "keyValue.h"
#include "sub.h"

#define PORT 4711
#define SEGSIZE sizeof(d_size)

int main() {
    char buffer[1024];
    int close_switch = 0; // Um Kindsprozesse Beenden zu können

    int rfd; // Rendevouz-Descriptor
//    int cfd; // Verbindungs-Descriptor

    int  id1 = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0777);
    data = (char*)shmat(id1, 0, 0);
    int  id2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0777);
    int *beg_switch = shmat(id2,0,0); // Switch für die Blockierung der andere Kindsprozesse wenn Beg aufgerufen wird
    int  exclusive_switch = 0; // Switch um Client zu identifizieren der BEG aufgerufen hat

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

    // Semaphor Gruppe anlegen
    int sem_id = semget (IPC_PRIVATE, 1, IPC_CREAT|0644);
    if (sem_id == -1) {
        perror ("Die Gruppe konnte nicht angelegt werden!");
        exit(1);
    }
    // Initilisierung der Semaphor. Semaphor wird  auf 1 gesetzt.
    unsigned short marker[1];
    marker[0] = 1;
    semctl(sem_id, 1, SETALL, marker);  // alle Semaphore auf 1
    // Structs für die Befehle für Eingang und Verlassen der kritische Zone
    struct sembuf enter, leave; // Structs für den Semaphor
    enter.sem_num = leave.sem_num = 0;  // Semaphor 0 in der Gruppe
    enter.sem_flg = leave.sem_flg = SEM_UNDO;
    enter.sem_op = -1; // blockieren, DOWN-Operation
    leave.sem_op = 1; // wider freigeben. Up Operation

    char out[out_size];

    int cnt = 0;
    while(close_switch == 0){
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
        char *ptr;
        // Creates a child process
        if (childpid = fork() == 0){ // FÜR MEHRERE CLIENTS VERANTWORTLICH !!!!!!!!!!
            // Closing the server socket id
            close(rfd);

            // Send a confirmation message to the client
            send(cfd, "hi client\n",strlen("hi client\n"), 0);

            // Lesen von Daten, die der Client schickt
            bytes_read = read(cfd, in, BUFSIZE);
            while (close_switch == 0) {
                while(*beg_switch == 1 && exclusive_switch == 0){
                    write(cfd, "Key/Value-Store blocked by exclusive session\n",45);
                    bytes_read = read(cfd, in, BUFSIZE);
                }


                ptr = strtok(in, delim);
                if(strcmp(ptr, "QUIT") == 0)
                {
                    close_switch = 1;
                }
                else if(strcmp(ptr, "BEG") == 0)
                {
                    semop(sem_id,&enter,1); // Down Operation, Eingang in kritischen Bereich
                    write(cfd, "Exclusive session started\n", 27);
                    *beg_switch = 1;
                    exclusive_switch = 1;
                }
                else if(strcmp(ptr, "END") == 0){
                    *beg_switch = 0;
                    exclusive_switch = 0;
                    write(cfd, "Exclusive session ended\n", 25);
                    semop(sem_id,&leave,1);
                }
                else {
                    proccess_client_input(&ptr, &out, in);
                    write(cfd, out, strlen(out));
                }

                if(close_switch == 0)
                    bytes_read = read(cfd, in, BUFSIZE);

            }
        }
    }
        close(cfd);
    shmdt(data);
    shmctl(id1, IPC_RMID, 0);
    // Rendevouz Descriptor schließen
    close(rfd);
}