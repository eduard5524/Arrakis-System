/*
*   PresetFunctions.h
*   @author Eduard Lecha Puig
*   @Created 2021-22
*   @brief PresetFunctions son utilities que es poden utilitzar al llarg 
*   del programa pels diferents móduls per tal de realitzar funcions específiques.
*   (c) Copyright La Salle
*
*/

#ifndef PRESETFUNCTIONS_H
#define PRESETFUNCTIONS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "PresetFunctions.h"

void tolowerCase(char* c);
char* read_until(int fd, char end);
char* read_until_different_options(int fd, char end, char end2, char* final);
int atoi(const char *str);


#endif