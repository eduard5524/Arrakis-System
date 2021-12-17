/*
*
*	@author Eduard Lecha Puig
*	@Created 2021-22
*	@brief PresetFunctions son utilities que es poden utilitzar al llarg 
*	del programa pels diferents móduls per tal de realitzar funcions específiques.
*	(c) Copyright La Salle
*
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "PresetFunctions.h"

typedef struct{
	int temps;
	char* ip;
	int port;
	char* location;
}Dades;

void getData(char* fileName, int* fd, Dades* dadesFitxer);
void freeDades(Dades* dadesFitxer);
char* readOrder();

#endif