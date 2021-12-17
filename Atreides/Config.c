/*
*
*	Config.c
* 	@author Eduard Lecha Puig
* 	@Created 2021-22
* 	@brief PresetFunctions son utilities que es poden utilitzar al llarg 
* 	del programa pels diferents móduls per tal de realitzar funcions específiques.
* 	(c) Copyright La Salle
*
*/

#include "Config.h"

//Definició de constants.
#define MSG_OPEN "Llegit el fitxer de configuració.\n"
#define MSG_ERROR_OPEN "There has been an error openning the file.\n"

char aux;
long result = -1;

/*
*	Funció que s'ocupa d'extruere l'informació del fitxer de configuració. 
*/
void getData(char* fileName, int* fd_file, Dades* dadesFitxer){
	char buffer[20];

	*fd_file = -1;
    *fd_file = open(fileName, O_RDONLY);
	
    if(*fd_file <= 0){
		write(1, MSG_ERROR_OPEN, strlen(MSG_ERROR_OPEN));
    }else{
        write(1, MSG_OPEN, strlen(MSG_OPEN));
		
		char final;

		dadesFitxer->port = -1;

		//Lectura de la @IP
		dadesFitxer->ip = read_until(*fd_file, '\n');
		sprintf(buffer, "%s\n", dadesFitxer->ip);	
		write(1, buffer, strlen(buffer));

		//Lectura del port
		char* aux_string = read_until_different_options(*fd_file, '\n', '\n', &final);
		dadesFitxer->port = atoi(aux_string);
		free(aux_string);
		sprintf(buffer, "%d\n", dadesFitxer->port);	
		write(1, buffer, strlen(buffer));

	
		//Lectura de la localització del programa Fremen.
		dadesFitxer->location = read_until_different_options(*fd_file, '\n', '\n', &final);
		write(1, dadesFitxer->location, strlen(dadesFitxer->location));
		sprintf(buffer, "%s\n", dadesFitxer->location);	
		write(1, buffer, strlen(buffer));
    }
}

void freeDades(Dades* dadesFitxer){
	free(dadesFitxer->ip);
	free(dadesFitxer->location);
}