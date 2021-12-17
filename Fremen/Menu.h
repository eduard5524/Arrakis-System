/*
*
*	@author Eduard Lecha Puig
*	@Created 2021-22
*	@brief Menu es una part per a tot el relatiu al menu.
*	(c) Copyright La Salle
*
*/

#ifndef MENU_H
#define MENU_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <Socket.h>

#include "PresetFunctions.h"


int getMenuOption(char* order);
char* getCommand(char* order);
char* readOrder();
int getNumberOfParameters(char* order);
void executeLogin(char* order, int fd_server);
#endif