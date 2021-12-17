/*
*   Socket.h
*   @author Eduard Lecha Puig
*   @Created 2021-22
*   @brief Socket s'utilitza per dur a terme el socket de servidor.
*   (c) Copyright La Salle
*
*/

#ifndef SOCKET_H
#define SOCKET_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/stat.h>
#include <netinet/in.h>

#include "PresetFunctions.h"

int launchServer(int port, char *ip, int* fd_socket);
int runServer(int fd_server);

void logic(int fd_client);

void handle_signal(int signum);

void closeSocket(int* fd_client);

#endif