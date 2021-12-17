/*
*   Socket.h
*   @author Eduard Lecha Puig
*   @Created 2021-22
*   @brief Socket s'encarrega de fer el Socket de connexió client.
*   (c) Copyright La Salle
*
*/

#ifndef SOCKET_H
#define SOCKET_H

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "PresetFunctions.h"

typedef struct{
    char origen[15]; 
    /*Origen: Array de 15 caràcters que contindrà el nom de qui envia la trama. Si el nom no 
    arriba a 15 caràcters, la resta de bytes s’han d’omplir amb ’\0’. Aquest camp sempre 
    ocupa exactament 15 bytes.*/

    char tipus[1];
    /*Tipus: Indica el tipus de trama que s’està enviant. Depenent de la trama aquesta tindrà 
    diferents valors tal i com s’especifica posteriorment. Aquest camp ocupa sempre només 
    1 byte.*/

    char data[240];
    /*Data: Camp de 240 bytes. Aquest camp serveix per emmagatzemar-hi valors o dades 
    que ha d’enviar la trama. Depenent del cas pot contenir diferents valors com s’especifica 
    en cada funcionalitat. En cas de que la informació no arribi als 240 bytes s’ompliran amb ’\0’.*/
}CommunicationData;

void close_connection();
int connect_to_server(char *ip, int port);
void start_session();
int openSocket(int* fd_server, char* ip, int port);
void sendMessage(int fd_server, CommunicationData dadesComunicacio);
void getMessage(int fd_server);
int closeSocket(int fd_server);


#endif